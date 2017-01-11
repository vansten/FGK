#include <cfloat>
#include "Timer.h"
#include "Camera.h"
#include "PhotonMap.h"
#include "StreamPhotonMap.h"

#define BIAS 0.001f
using namespace std;
Camera::Camera()
{
    position.Zero();
    target.Zero();
    target.z = 1;
    nearPlane = 0.001f;
    farPlane = 1000;
    fov = 54;
    img = 0;
    renderFileName = "render";
}

Camera::Camera(Vector3 positon, Vector3 target, float nearPlane, float farPlane, float fov) {
    this->position = positon;
    this->target = target;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
    this->fov = fov;
    img=0;
    renderFileName = "render";
}


/**
  Recalculates camera projection and view matrices.
  */
void Camera::Recalculate() {
    if(img) {
        projectionMatrix.SetPerspective(fov, ((float)img->GetWidth())/img->GetHeight(), nearPlane, farPlane);

        distance = 1.0f/tanf(fov/2);
        viewMatrix.LoadIdentity();

        Vector3 direction = target - position;
        direction.Normalize();

        //up vector is always up
        Vector3 up = Vector3(0,1,0);

        Vector3 left = up.CrossProduct(direction);
        left.Normalize();

        viewMatrix.SetRow(0, Vector4(left, 0.0f));
        viewMatrix.SetRow(1, Vector4(up, 0.0f));
        viewMatrix.SetRow(2, Vector4(direction, 0.0f));
        viewMatrix.SetRow(3, Vector4(0, 0, 0, 1));

        Matrix4x4 trans;
        trans.SetTranslation(-position);
        viewMatrix = viewMatrix*trans;

        vpMatrix = viewMatrix;
        invVPMatrix = vpMatrix.GetInverse();
    }
}

void Camera::RenderScene(Scene* scene, unsigned int ns) {

	Timer t;

    Recalculate();

    float pixelW = 1.0f/img->GetWidth();
    float pixelH = 1.0f/img->GetHeight();

    int numSamples=ns;
    if(img) {
        img->Clear(LightIntensity(0,0,0));


        #pragma omp parallel for schedule(dynamic, 50)
        for(unsigned int i=0;i<img->GetWidth()*img->GetHeight();i++) {
            float x = i % img->GetWidth();
            float y = i / img->GetWidth();

            LightIntensity currentPixel;
            for(int sY=-numSamples/2;sY<=numSamples/2;sY++) {
                for(int sX=-numSamples/2;sX<=numSamples/2;sX++) {

                    //cast ray into image
                    float px = 2.0f*((x+pixelW/numSamples*sX)/img->GetWidth()) - 1.0;
                    float py = 2.0f*((y+pixelH/numSamples*sY)/img->GetHeight()) - 1.0;
                    py*=-1;
                    px /= projectionMatrix.entries[0];
                    py /= projectionMatrix.entries[5];

                    Vector4 origin(0,0,0,1);
                    Vector4 direction(px,py, 1, 0);

                    origin = invVPMatrix*Vector4(origin);
                    direction = invVPMatrix*Vector4(direction);

                    Ray ray(Vector3(origin.x, origin.y, origin.z), Vector3(direction.x, direction.y, direction.z));

                    //and trace it
                    currentPixel+=rayTracer.TraceRay(ray, scene, position, 6);
                }
            }
            img->SetPixel(x,y,currentPixel/(numSamples*numSamples));
        }

		m_renderingTime = t.GetElapsedMS();
		printf("Rendering time: %f", m_renderingTime);
        //qDebug()<<"Rendering time " << m_renderingTime <<"ms";
		//
        //img->SaveToFile(renderFileName);
    }
}

void Camera::RenderSceneStream(Scene* scene, unsigned int ns, unsigned int m_numEmittedGlobalPhotons,
                               unsigned int m_numEmittedCausticPhotons, int numAssociatedPhotons, float radius, int reflections) {
	Timer t;

    Recalculate();

    float pixelW = 1.0f/img->GetWidth();
    float pixelH = 1.0f/img->GetHeight();

    int numSamples=ns;
    if(img) {
        img->Clear(LightIntensity(0,0,0));

		t.Restart();

        StreamPhotonMap photonMap;
        photonMap.SetNumAssociatedPhotons(numAssociatedPhotons);
        photonMap.SetRadius(radius);


        //qDebug()<<"generuje mape globalna";
        photonMap.GeneratePhotonMap(scene, m_numEmittedGlobalPhotons, reflections);

        // KAUSTYKA
        StreamPhotonMap causticPhotonMap;
        causticPhotonMap.SetNumAssociatedPhotons(numAssociatedPhotons);
        causticPhotonMap.SetRadius(radius);

        //qDebug()<<"generuje mape kaustyczna";
        causticPhotonMap.GeneratePhotonMap(scene, m_numEmittedCausticPhotons, 4, true);

		m_renderingTime = t.GetElapsedMS();
        //qDebug()<<"Photon tracing time " << m_renderingTime <<"ms";

		t.Restart();

        //qDebug()<<"w scenie jest "<<scene->geometry.count()<<" obiektow";
        // przed renderingiem usun sciane frontowa ktora sluzyla tylko do odbijania fotonow podczas propagacji aby nie uciekaly ze sceny
        scene->geometry.front()->deleteFrontWall();
        //qDebug()<<"zaczynam renderowac";

        //wrong sampling method
        /*
        #pragma omp parallel for schedule(dynamic, 50)
        for(unsigned int i=0;i<img->GetWidth()*img->GetHeight();i++) {
            float x = i % img->GetWidth();
            float y = i / img->GetWidth();

            LightIntensity currentPixel;
            for(int sY=-numSamples/2;sY<=numSamples/2;sY++) {
                for(int sX=-numSamples/2;sX<=numSamples/2;sX++) {
                    float px = 2.0f*((x+pixelW/numSamples*sX)/img->GetWidth()) - 1.0;
                    float py = 2.0f*((y+pixelH/numSamples*sY)/img->GetHeight()) - 1.0;
                    py*=-1;
                    px /= projectionMatrix.entries[0];
                    py /= projectionMatrix.entries[5];

                    Vector4 origin(0,0,0,1);
                    Vector4 direction(px,py, 1, 0);

                    origin = invVPMatrix*Vector4(origin);
                    direction = invVPMatrix*Vector4(direction);

                    Ray ray(Vector3(origin.x, origin.y, origin.z), Vector3(direction.x, direction.y, direction.z));

                    currentPixel+=rayTracer.TraceRayStream(ray, scene, position, 6, 1050, &photonMap, &causticPhotonMap); // default exposure = 750
                    ileprobek++;
                }
            }
            img->SetPixel(x,y,currentPixel/ileprobek);//(numSamples*numSamples));
        }
        */

        //one sample per pixel
        if(numSamples==1)
        {
            float pxWidth = 2.0f / img->GetWidth();
            float pxHeight = 2.0f / img->GetHeight();
            for(int j=0; j<img->GetHeight();j++)
            {
                for(int i=0;i<img->GetWidth();i++)
                {
                    LightIntensity currentPixel;
                    //dla kazdego piksela rzutuj promien przez jego srodek
                    float pX = -1.0 + (i+ 0.5 )*pxWidth;
                    float pY = 1.0 - (j+ 0.5 )*pxHeight;
                    pX /= projectionMatrix.entries[0];
                    pY /= projectionMatrix.entries[5];

                    Vector4 origin(0,0,0,1);
                    Vector4 direction(pX,pY, 1, 0);

                    origin = invVPMatrix*Vector4(origin);
                    direction = invVPMatrix*Vector4(direction);

                    Ray ray(Vector3(origin.x, origin.y, origin.z), Vector3(direction.x, direction.y, direction.z));
                    currentPixel+=rayTracer.TraceRayStream(ray, scene, position, 6, 1050, &photonMap, &causticPhotonMap); // default exposure = 750
                    img->SetPixel(i,j,currentPixel/numSamples);
                }
            }
        }
        // stochastic oversampling for multiple samples per pixel
        else
        {
            float losoweX, losoweY;
            float pxWidth = 2.0f / img->GetWidth();
            float pxHeight = 2.0f / img->GetHeight();
            for(int j=0; j<img->GetHeight();j++)
            {
                for(int i=0;i<img->GetWidth();i++)
                {
                    LightIntensity currentPixel;
                    //dla kazdego piksela rzutuj n promieni
                    for(int n=0;n<numSamples;n++)
                    {
                        //obliczanie losowej pozycji wewnatrz piksela

                        losoweX = -1.0 + (i+ (static_cast <float>(rand()/static_cast <float> (RAND_MAX))) )*pxWidth;
                        losoweY = 1.0 - (j+ (static_cast <float>(rand()/static_cast <float> (RAND_MAX))) )*pxHeight;
						losoweX /= projectionMatrix.entries[0];
                        losoweY /= projectionMatrix.entries[5];

                        Vector4 origin(0,0,0,1);
                        Vector4 direction(losoweX,losoweY, 1, 0);

                        origin = invVPMatrix*Vector4(origin);
                        direction = invVPMatrix*Vector4(direction);

                        Ray ray(Vector3(origin.x, origin.y, origin.z), Vector3(direction.x, direction.y, direction.z));
                        currentPixel+=rayTracer.TraceRayStream(ray, scene, position, 6, 1050, &photonMap, &causticPhotonMap); // default exposure = 750
                    }
                    //qDebug()<<tempprobek;
                    img->SetPixel(i,j,currentPixel/numSamples);
                }
            }
        }

		m_renderingTime = t.GetElapsedMS();
        //qDebug()<<"Rendering time " << m_renderingTime <<"ms";

		char buff[1000];
		snprintf(buff, sizeof(buff), "spm_%s_%s_%s_%s_%s_%s", std::to_string(ns).c_str(), std::to_string(m_numEmittedGlobalPhotons).c_str(), std::to_string(m_numEmittedCausticPhotons).c_str(), std::to_string(numAssociatedPhotons).c_str(), std::to_string(radius).c_str(), std::to_string(m_renderingTime).c_str());
		renderFileName = buff;
        //img->SaveToFile(renderFileName);
    }
}

void Camera::RenderScene(Scene* scene, unsigned int ns, unsigned int numGlobalMapPhotons,
                         unsigned int numCausticMapPhotons)
{
	Timer t;
    Recalculate();

    float pixelW = 1.0f/img->GetWidth();
    float pixelH = 1.0f/img->GetHeight();

    int numSamples=ns;
    if(img) {
        img->Clear(LightIntensity(0,0,0));

        PhotonMap photonMap;

        photonMap.GeneratePhotonMap(scene, numGlobalMapPhotons, 6);

        PhotonMap causticPhotonMap;
        causticPhotonMap.GeneratePhotonMap(scene, numCausticMapPhotons, 2, true);
		t.Restart();
		#pragma omp parallel for schedule(dynamic, 50)
        for(unsigned int i=0;i<img->GetWidth()*img->GetHeight();i++) {
            float x = i % img->GetWidth();
            float y = i / img->GetWidth();

            LightIntensity currentPixel;
            for(int sY=-numSamples/2;sY<=numSamples/2;sY++) {
                for(int sX=-numSamples/2;sX<=numSamples/2;sX++) {
                    float px = 2.0f*((x+pixelW/numSamples*sX)/img->GetWidth()) - 1.0;
                    float py = 2.0f*((y+pixelH/numSamples*sY)/img->GetHeight()) - 1.0;
                    py*=-1;
                    px /= projectionMatrix.entries[0];
                    py /= projectionMatrix.entries[5];

                    Vector4 origin(0,0,0,1);
                    Vector4 direction(px,py, 1, 0);

                    origin = invVPMatrix*Vector4(origin);
                    direction = invVPMatrix*Vector4(direction);

                    Ray ray(Vector3(origin.x, origin.y, origin.z), Vector3(direction.x, direction.y, direction.z));

                    currentPixel+=rayTracer.TraceRay(ray, scene, position, 6, 750, &photonMap,&causticPhotonMap);
                }
            }
            img->SetPixel(x,y,currentPixel/(numSamples*numSamples));
        }

        m_renderingTime = t.GetElapsedMS();
        //qDebug()<<"Rendering time " << m_renderingTime <<"ms";

		char buff[1000];
		snprintf(buff, sizeof(buff), "pm_%s_%s_%s_%s", std::to_string(ns).c_str(), std::to_string(numGlobalMapPhotons).c_str(), std::to_string(numCausticMapPhotons).c_str(), std::to_string(m_renderingTime).c_str());
		renderFileName = buff;
        //img->SaveToFile(renderFileName);
    }
}

void Camera::VisualizePhotonMap(Scene *scene, int numPhotons, int maxReflections)
{
	Timer t;
     Recalculate();
    if(img) {
        img->Clear(LightIntensity(0,0,0));

        PhotonMap photonMap;

        photonMap.GeneratePhotonMap(scene, numPhotons, maxReflections, true);

		t.Restart();
        #pragma omp parallel for
        for(unsigned int i=0;i<img->GetWidth()*img->GetHeight();i++) {
            float x = i % img->GetWidth();
            float y = i / img->GetWidth();
            float X,Y;
            X=x;
            Y=y;

            x= 2.0f*(x/img->GetWidth())-1.0f;
            y= 2.0f*(y/img->GetHeight())-1.0f;
            y*=-1;
            x /= projectionMatrix.entries[0];
            y /= projectionMatrix.entries[5];

            Vector4 origin(0,0,0,1);
            Vector4 direction(x,y, 1, 0);

            origin = invVPMatrix*Vector4(origin);
            direction = invVPMatrix*Vector4(direction);

            Ray ray(Vector3(origin.x, origin.y, origin.z), Vector3(direction.x, direction.y, direction.z));

            LightIntensity resultIntensity;

            int closest=-1;
            float closestDist=FLT_MAX;
            IntersectionResult closestIntersection;

            IntersectionResult result;
			auto geometryIt = scene->geometry.begin();
			auto geometryEnd = scene->geometry.end();
			int j = 0;
			for(geometryIt; geometryIt != geometryEnd; ++geometryIt, ++j)
			{
				result = (*geometryIt)->Intersects(ray);
				    if(result.type!=MISS) {
				        if(closestDist>result.distance) {
				            closestDist = result.distance;
				            closest = j;
				            closestIntersection = result;
				        }
				    }
			}
            

            if(closest!=-1) {
                if(closestIntersection.object->GetMaterial()->type==REFLECTIVE) {
                    resultIntensity = LightIntensity(0,0,0);
                }
                else if(closestIntersection.object->GetMaterial()->type==REFRACTIVE) {

                    resultIntensity = LightIntensity(0,0,0);
                }
                else {
                    //QList<Photon*> closest = photonMap.GetClosestPhotons(closestIntersection.point, 0.1, 2);

                    //if(closest.count()!=0) {
                    //    float r = (closest[0]->position-closestIntersection.point).GetLength();
					//
                    //    LightIntensity E;
                    //    for(int z=0;z<closest.count();z++) {
                    //        float dot = closestIntersection.intersectionPointNormal.DotProduct(closest[z]->direction);
                    //        if(dot>0) {
                    //            E += 2000*closest[z]->energy*dot;
                    //        }
                    //    }
					//
					//
                    //    resultIntensity += (E/(M_PI*r*r));
                    //}
                }
            }
            img->SetPixel(X,Y,resultIntensity);
        }

		m_renderingTime = t.GetElapsedMS();
        //qDebug()<<"Rendering time " << m_renderingTime <<"ms";

		char buff[1000];
		snprintf(buff, sizeof(buff), "vpm_%s_%s_%s", std::to_string(numPhotons).c_str(), std::to_string(maxReflections).c_str(), std::to_string(m_renderingTime).c_str());
		renderFileName = buff;
        //img->SaveToFile(renderFileName);
    }
}


void Camera::VisualizeStreamPhotonMap(Scene *scene, int numPhotons, int maxReflections, int numAssociatedPhotons, float radius)
{
	Timer t;
    Recalculate();
    if(img) {
        img->Clear(LightIntensity(0,0,0));

        StreamPhotonMap photonMap;
        photonMap.SetNumAssociatedPhotons(numAssociatedPhotons);
        photonMap.SetRadius(radius);

        photonMap.GeneratePhotonMap(scene, numPhotons, maxReflections, false);

		t.Restart();
        #pragma omp parallel for
        for(unsigned int i=0;i<img->GetWidth()*img->GetHeight();i++) {
            float x = i % img->GetWidth();
            float y = i / img->GetWidth();
            float X,Y;
            X=x;
            Y=y;

            x= 2.0f*(x/img->GetWidth())-1.0f;
            y= 2.0f*(y/img->GetHeight())-1.0f;
            y*=-1;
            x /= projectionMatrix.entries[0];
            y /= projectionMatrix.entries[5];

            Vector4 origin(0,0,0,1);
            Vector4 direction(x,y, 1, 0);

            origin = invVPMatrix*Vector4(origin);
            direction = invVPMatrix*Vector4(direction);

            Ray ray(Vector3(origin.x, origin.y, origin.z), Vector3(direction.x, direction.y, direction.z));

            LightIntensity resultIntensity;

            int closest=-1;
            float closestDist=FLT_MAX;
            IntersectionResult closestIntersection;

            IntersectionResult result;
			auto geometryIt = scene->geometry.begin();
			auto geometryEnd = scene->geometry.end();
			int j = 0;
			for(geometryIt; geometryIt != geometryEnd; ++geometryIt, ++j)
			{
				result = (*geometryIt)->Intersects(ray);
				if(result.type != MISS)
				{
					if(closestDist>result.distance)
					{
						closestDist = result.distance;
						closest = j;
						closestIntersection = result;
					}
				}
			}

            if(closest!=-1) {
                if(closestIntersection.object->GetMaterial()->type==REFLECTIVE) {
                    resultIntensity = LightIntensity(0,0,0);
                }
                else if(closestIntersection.object->GetMaterial()->type==REFRACTIVE) {

                    resultIntensity = LightIntensity(0,0,0);
                }
                else {
                    //QList<Stream*> closest = photonMap.GetClosestPhotons(closestIntersection.point, 0.1f, 2); //second param is the searching radius -> size of the "visualized dot"

                    //if(closest.count()!=0) {
                    //    float r = (closest[0]->position-closestIntersection.point).GetLength();
					//
                    //    LightIntensity E;
                    //    for(int z=0;z<closest.count();z++) {
                    //        //qDebug()<<closest[z]->associatedPhoton.count();
                    //        for(int j=0;j<closest[z]->associatedPhoton.count();j++) {
                    //            float dot = closestIntersection.intersectionPointNormal.DotProduct(closest[z]->associatedPhoton[j].direction);
                    //            if(dot>0) {
                    //                E += 2000*closest[z]->associatedPhoton[j].energy*dot;
                    //            }
                    //        }
					//
                    //        float dot = closestIntersection.intersectionPointNormal.DotProduct(closest[z]->leadingPhoton.direction);
                    //        if(dot>0) {
                    //            E += 2000*closest[z]->leadingPhoton.energy*dot;
                    //        }
                    //    }
					//
                    //    resultIntensity += (E/(M_PI*r*r));
                    //}
                }
            }
            img->SetPixel(X,Y,resultIntensity);
        }

		m_renderingTime = t.GetElapsedMS();
        //qDebug()<<"Rendering time " << m_renderingTime <<"ms";
		//
		char buff[1000];
		snprintf(buff, sizeof(buff), "vspm_%s_%s_%s_%s_%s", std::to_string(numPhotons).c_str(), std::to_string(maxReflections).c_str(), std::to_string(numAssociatedPhotons).c_str(), std::to_string(radius).c_str(), std::to_string(m_renderingTime).c_str());
		renderFileName = buff;
        //img->SaveToFile(renderFileName);
    }
}
