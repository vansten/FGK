#include "AreaLight.h"

AreaLight::AreaLight(Vector3 center, Vector2 size, Color color, Vector3 attenuation, int density) {
    float stepX = size.x/(density);
    float stepY = size.y/(density);
    Vector3 corner = center - Vector3(size.x, 0, size.y);

    for(int y=-density/2;y<=density/2;y++) {
        for(int x=-density/2;x<=density/2;x++) {
            PointLight* p = new PointLight(center+Vector3(x*stepX, 0, y*stepY), color/(density*density), attenuation);
            lights.push_back(p);
        }
    }
    //qDebug()<<"liczba swiatel punktowych dla swiatla powierzchniowego"<<lights.count();
	inShadows.resize(lights.size());

    this->center = center;
    this->size = size;

    type = LightSourceType::AREA;
}


AreaLight::~AreaLight() {
	auto it = lights.begin();
	auto end = lights.end();
    for(it; it != end; ++it)
        delete (*it);
    lights.clear();
    inShadows.clear();
}

bool AreaLight::IsInShadow(IntersectionResult *ir, std::list<Geometry *> &geometry) {
    return false;
}

LightIntensity AreaLight::GetLightIntensity(Vector3 cameraPosition, IntersectionResult *ir, std::list<Geometry *> &geometry) {
    LightIntensity result;
	unsigned int size = lights.size();
	for(unsigned int i = 0; i < size; ++i)
	{
		if(!inShadows.at(i))
        result+=lights.at(i)->GetLightIntensity(cameraPosition, ir, geometry);
    }
    return result;///lights.count();
}

Ray AreaLight::GetPhoton(bool useProjectionMap) const {

    int i = rand()%lights.size();
	
    Ray r = lights.at(i)->GetPhoton(useProjectionMap);
	
    if(r.direction.DotProduct(Vector3(0,-1,0))<0) {
        r = Ray(r.origin, -r.direction);
    }
	
    return r;
}

void AreaLight::CreateProjectionMap(const Scene* scene) {
	unsigned int size = lights.size();
	for(unsigned int i = 0; i < size; ++i)
	{
        //qDebug()<<i;
        lights.at(i)->CreateProjectionMap(scene);
    }
}

float AreaLight::GetProjectionMapRatio() const {
    float avg=0;
	unsigned int size = lights.size();
	for(unsigned int i = 0; i < size; ++i)
        avg += lights.at(i)->GetProjectionMapRatio();
	
    return avg/size;
}
