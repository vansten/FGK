#include "StreamPhotonMap.h"
#include <cfloat>
#include "KDTree.h"
#include "Lights/AreaLight.h"
#include "ConsolePanel.h"

#define BIAS 0.001f

const float RADIUS=2.5;

StreamPhotonMap::StreamPhotonMap() {
    maxPhotons=9000000;
    kdTree = new KDTree<Stream>();
}

StreamPhotonMap::~StreamPhotonMap() {
	auto photonsIt = photons.begin();
	auto photonsEnd = photons.end();
	for(photonsIt; photonsIt != photonsEnd; ++photonsIt)
	{
		delete (*photonsIt);
	}
	photons.clear();

    delete kdTree;
}


void StreamPhotonMap::GeneratePhotonMap(Scene *scene, int numPhotons, int maxReflections, bool caustic) {
    int numPointLights = 0;
    //count how much points lights are in scene
	auto lightsIt = scene->lights.begin();
	auto lightsEnd = scene->lights.end();
	for(lightsIt; lightsIt != lightsEnd; ++lightsIt)
	{
        if((*lightsIt)->type==LightSourceType::POINT || (*lightsIt)->type == LightSourceType::AREA) {
            numPointLights++;
            if(caustic) {
                //if we generate caustic map, we must generate first projection map for each light
                printf("generuje mape projekcji dla swiatla");
				(*lightsIt)->CreateProjectionMap(scene);
            }
        }
    }
	printf("Liczba swiatel w scenie %i", numPointLights);

    //adjust number of photons for each light
	if(numPointLights != 0)
	{
		numPhotons /= numPointLights;
	}

	for(lightsIt = scene->lights.begin(); lightsIt != lightsEnd; ++lightsIt)
	{
        if((*lightsIt)->type==LightSourceType::POINT || (*lightsIt)->type==LightSourceType::AREA)
            //generate photons for each light in scene
	
            printf("emituje fotony dla zrodla");
	
        printf("dla kazdego fotonu ze zrodla ma byc %i odbic", maxReflections);
            GeneratePhotons((*lightsIt), &scene->geometry, numPhotons, caustic, maxReflections);
    }


    //build kdtree from photons
    kdTree->Build(photons);
    photons.clear();
}

//generate streams for given light

void StreamPhotonMap::GeneratePhotons(AmbientLight *light, std::list<Geometry*>* geometry, int numPhotons, bool caustic, int maxReflections) {

    std::list<Stream*> tempPhotons;
	Logger() << "mam wyemitowac " << numPhotons << " fotonow\n";
    int emittedPhotons = 0;

    //while(tempPhotons.count()<numPhotons && photons.count()+tempPhotons.count()<maxPhotons) {
    //while(tempPhotons.count()<numPhotons) {
    while(emittedPhotons<numPhotons && photons.size()+tempPhotons.size()<maxPhotons) {
        Ray photonRay;
        //Logger()<<tempPhotons.count();
        //generate lead photon
        photonRay = light->GetPhoton(caustic);

        //Logger()<<"wyemitowalem foton wiodacy";
        Stream startStream;
        //jesli jest to foton niekaustyczny to wygeneruj fotony stowarzyszone w strumieniu
        if(!caustic)
        {
            //add associated photons.
            //At begining all associated photons have the same position as lead photon and energy = 1 / assoc photons count
            for(int j=0;j<numAssociatedPhotons;j++) {
                SinglePhoton sp;
                sp.position = photonRay.origin;
                sp.energy = light->color/numAssociatedPhotons;
                startStream.associatedPhoton.push_back(sp);
            }
        }
        //Logger()<<"Poczatkowo strumien ma"<<startStream.associatedPhoton.count()<<"fotonow stowarzyszonych";
        TracePhoton(light->color, photonRay, geometry, &tempPhotons, &startStream, maxReflections);
        //Logger()<<"koniec "<<tempPhotons.count();
        emittedPhotons++;
    }
    Logger() << "Wyemitowalem " << emittedPhotons << " fotonow wiodacych";

    //przeskaluj energie kazdego fotonu przez liczbe zapisanych do mapy fotonow
    float scale;
    if(caustic) {
        if(light->type == LightSourceType::POINT || light->type == LightSourceType::AREA)
            scale = (1.0f/tempPhotons.size())*light->GetProjectionMapRatio();
    }
    else
        scale = 1.0f/tempPhotons.size();

	auto tempPhotonsIt = tempPhotons.begin();
	auto tempPhotonsEnd = tempPhotons.end();
	for(tempPhotonsIt; tempPhotonsIt != tempPhotonsEnd; ++tempPhotonsIt)
	{
		photons.push_back(*tempPhotonsIt);
        (*tempPhotonsIt)->leadingPhoton.energy*=scale;
		auto associatedIt = (*tempPhotonsIt)->associatedPhoton.begin();
		auto associatedEnd = (*tempPhotonsIt)->associatedPhoton.end();
        for(associatedIt; associatedIt != associatedEnd; ++associatedIt)
            (*associatedIt).energy*=scale;
    }

    Logger() << "Mapa fotonowa zawiera " << (int)photons.size() <<  " fotonow (wyemitowane + odbite)";
}


//traces photon stream
void StreamPhotonMap::TracePhoton(LightIntensity photonEnergy, const Ray &startRay, std::list<Geometry*> *geometry,
                            std::list<Stream *> *photons, Stream* parent, int reflections) {

    int closest=-1;
    float closestDist=FLT_MAX;
    IntersectionResult closestIntersection;

    IntersectionResult result;
    //check intersection of lead photon with geometry in scene
	auto geometryIt = geometry->begin();
	auto geometryEnd = geometry->end();
	int j = 0;
	for(geometryIt; geometryIt != geometryEnd; ++geometryIt, ++j)
	{
        result = (*geometryIt)->Intersects(startRay);
        if(result.type!=MISS) {
            if(closestDist>result.distance) {
                closestDist = result.distance;
                closest = j;
                closestIntersection = result;
            }
        }
    }


    if(closest!=-1) {
        //if photon intersects with reflective object and we can still reflect photon
        if(closestIntersection.object->GetMaterial()->type==REFLECTIVE && reflections>0) {
            Vector3 reflected = startRay.direction.Reflect(closestIntersection.intersectionPointNormal);
            reflected.Normalize();
            Ray newRay(closestIntersection.point+reflected*BIAS, reflected);


            //zlicz energie stowarzyszonych fotonow i przekaz ja do wiodacego fotonu (koncentracja energii dla uwydatnienia kaustyki)
            LightIntensity tempE;
			auto associatedIt = parent->associatedPhoton.begin();
			auto associatedEnd = parent->associatedPhoton.end();
			for(associatedIt; associatedIt != associatedEnd; ++associatedIt)
			{
                tempE += (*associatedIt).energy;
            }
            photonEnergy += tempE;

            //temporary parent stream with no associated photons
            Stream tempStream;

            TracePhoton(photonEnergy, newRay, geometry, photons, &tempStream, reflections-1);
        }
        else if(closestIntersection.object->GetMaterial()->type==REFRACTIVE && reflections>0) {
            RefractiveMaterial* mat = (RefractiveMaterial*)closestIntersection.object->GetMaterial();

            Vector3 refracted;
            if(closestIntersection.type==HIT)
                refracted = startRay.direction.Refract(closestIntersection.intersectionPointNormal,
                                                  mat->etaRate);
            else
                refracted = startRay.direction.Refract(-closestIntersection.intersectionPointNormal,
                                                  1.0f/mat->etaRate);
            refracted.Normalize();

            Ray newRay(closestIntersection.point+refracted*BIAS, refracted);

            //zlicz energie stowarzyszonych fotonow i przekaz ja do wiodacego fotonu (koncentracja energii dla uwydatnienia kaustyki)
            LightIntensity tempE;
			auto associatedIt = parent->associatedPhoton.begin();
			auto associatedEnd = parent->associatedPhoton.end();
			for(associatedIt; associatedIt != associatedEnd; ++associatedIt)
			{
				tempE += (*associatedIt).energy;
			}
            photonEnergy += tempE;
            //temporary parent stream with no associated photons
            Stream tempStream;

            TracePhoton(photonEnergy, newRay, geometry, photons, &tempStream, reflections-1);
        }
        else {
            //we hit diffuse geometry
            //Logger()<<"wiodacy trafil w dyfuzyjna";

            DiffuseMaterial* mat = (DiffuseMaterial*)closestIntersection.object->GetMaterial();

            //new photon stream to store in stream map
            Stream* newStream = new Stream;
            newStream->leadingPhoton.energy = photonEnergy;
            newStream->leadingPhoton.position = closestIntersection.point;
            newStream->position = closestIntersection.point;
            newStream->leadingPhoton.direction = -startRay.direction;

            //tymczasowa lista do przechowywania odbitych fotonow stowarzyszonych
            std::vector<SinglePhoton> reflectedAssocPhotons;

            //Logger()<<"energia zapisanego fotonu wiodacego: "<<photonEnergy.r<<photonEnergy.g<<photonEnergy.b;

            //generate new associated photons
            int ileAssoc = 0;
            //Logger()<<"dotychczas w strumieniu bylo: "<<parent->associatedPhoton.count();
            //Logger()<<"dotychczasowy promien strumienia: "<<radius;
			auto associatedIt = parent->associatedPhoton.begin();
			auto associatedEnd = parent->associatedPhoton.end();
			for(associatedIt; associatedIt != associatedEnd; ++associatedIt)
			{
                float x,y,z;
                do 
				{
					//((float)qrand())/RAND_MAX-1.0f;
                    x = 2.0f*(static_cast <float>(rand()/static_cast <float>(RAND_MAX)))-1.0f;
                    y = 2.0f*(static_cast <float>(rand()/static_cast <float>(RAND_MAX)))-1.0f;
                    z = 2.0f*(static_cast <float>(rand()/static_cast <float>(RAND_MAX)))-1.0f;
                } while(x*x+y*y+z*z>1);
                //pozycja punktu koncowego wektora wyznaczajacego nowy foton stowarzyszony
                Vector3 newAssociatedPos(x,y,z);
                newAssociatedPos*=radius;
                newAssociatedPos += closestIntersection.point;

                //check if ray from old associated photon to new intersects something
                /*
                Ray oldAssociatedToNew(parent->associatedPhoton[j].position, newAssociatedPos - parent->associatedPhoton[j].position);
                IntersectionResult iresult;
                for(int k=0;k<geometry->count();k++) {
                    iresult = geometry->at(k)->Intersects(oldAssociatedToNew, (newAssociatedPos - parent->associatedPhoton[j].position).GetLength());
                    if(iresult.type!=MISS) {
                       break;
                    }
                }
                */

                //check if ray from old associated photon to new temp point intersects something
                int closestFlag=-1;
                float closestDistance=FLT_MAX;
                IntersectionResult tempClosestIntersection;
                Ray oldAssociatedToNew((*associatedIt).position, newAssociatedPos - (*associatedIt).position);
                IntersectionResult iresult;
				auto geometryIt = geometry->begin();
				auto geometryEnd = geometry->end();
				int k = 0;
                for(geometryIt; geometryIt != geometryEnd; ++geometryIt, ++k)
				{
                    iresult = (*geometryIt)->Intersects(oldAssociatedToNew);//, (newAssociatedPos - parent->associatedPhoton[j].position).GetLength());
                    if(iresult.type!=MISS) {
                        if(closestDistance>iresult.distance) {
                            closestDistance = iresult.distance;
                            closestFlag = k;
                            tempClosestIntersection = iresult;
                        }
                    }
                }

                //jesli promieñ nowego fotonu trafil w geometrie
                if(tempClosestIntersection.type!=MISS)
                {

                    //Logger()<<"znalazlem przeciecie stowarzyszonego";
                    DiffuseMaterial* tempMat = (DiffuseMaterial*)tempClosestIntersection.object->GetMaterial();

                    //sprawdz czy przeciecie najblizsze wzgledem starej pozycji fotonu stowarzyszonego
                    //jest w odleglosci wiekszej niz promien strumienia od nowej pozycji fotonu wiodacego
                    if( (tempClosestIntersection.point - newStream->leadingPhoton.position).GetLength() > radius)
                    {
                        //Logger()<<"foton stowarzyszony zablokowany";
                        continue;
                    }
                    //jesli przeciecie w odleglosci mniejszej niz promieñ strumienia to sprawdz material
                    else if(tempMat->type == DIFFUSE)
                    {
                        //Logger()<<"foton stowarzyszony trafil w powierzchnie dyfuzyjna"<<tempMat->diffuse.r<<tempMat->diffuse.g<<tempMat->diffuse.b;

                        //utworz nowy foton stowarzyszony w znalezionym punkcie przeciecia
                        SinglePhoton newAssociated;
                        newAssociated.position = tempClosestIntersection.point;
                        newAssociated.direction = -oldAssociatedToNew.direction;
                        newAssociated.energy = (*associatedIt).energy;
                        newStream->associatedPhoton.push_back(newAssociated);
                        //jego energia po ewentualnym odbiciu bedzie rowna
                        SinglePhoton reflectedAssociated;
                        reflectedAssociated.position = tempClosestIntersection.point;
                        reflectedAssociated.direction = -oldAssociatedToNew.direction;
                        reflectedAssociated.energy = newAssociated.energy*tempMat->diffuse;
                        reflectedAssocPhotons.push_back(reflectedAssociated);
                        //Logger()<<"poprzednia energia stowarzyszonego fotonu"<<newAssociated.energy.r<<newAssociated.energy.g<<newAssociated.energy.b;
                        //Logger()<<"energia po odbiciu stowarzyszonego fotonu"<<reflectedAssociated.energy.r<<reflectedAssociated.energy.g<<reflectedAssociated.energy.b;
                        ileAssoc++;
                    }
                    else{
                        //Logger()<<"foton stowarzyszony trafil w powierzchnie niedyfuzyjna";
                    }
                }

            }
            Logger()<<"wyemitowalem"<<ileAssoc<<"fotonow stowarzyszonych\n";

            /*
            if(newStream->associatedPhoton.count())
                newStream->leadingPhoton.energy = photonEnergy/newStream->associatedPhoton.count();
            for(int j=0;j<newStream->associatedPhoton.count();j++)
                newStream->associatedPhoton[j].energy = photonEnergy/newStream->associatedPhoton.count();
            */

            //zapisz strumien fotonow do mapy strumieni
			photons->push_back(newStream);

            //jesli nastapilo odbicie
            if(PropabilityOfAbsorption()>mat->absorptionPropability && reflections>0) {
                //heurystyka Jensena bazujaca na mechanizmie rosyjskiej ruletki
                //float avgDiff = (mat->diffuse.r+mat->diffuse.g+mat->diffuse.b)/3;
                //photonEnergy *= (mat->diffuse/avgDiff);

                //przeskaluj energie fotonu po odbiciu od materialu oraz fotonow stowarzyszonych
                photonEnergy *= mat->diffuse;
                newStream->associatedPhoton = reflectedAssocPhotons;

                // odbij tylko jesli foton po odbiciu ma energie wieksza od zera (aby nie sledzic i zapisywac fotonow z energia 0,0,0 w rezultacie odbicia np czerwonego od niebieskiego)
                if (photonEnergy.r+photonEnergy.g+photonEnergy.b != 0)
                {
                    Vector3 reflected = LambertReflectionDirection(closestIntersection);
                    Ray newRay(closestIntersection.point+reflected*BIAS, reflected);
                    TracePhoton(photonEnergy, newRay, geometry, photons, newStream, reflections-1);
                }
            }
        }

    }
    else{//jesli nie trafilismy w nic lub blad numeryczny szukania przeciecia
        Logger()<<"pudlo\n";
    }
}

float StreamPhotonMap::PropabilityOfAbsorption() {
    return ((float)rand())/RAND_MAX;
}

Vector3 StreamPhotonMap::LambertReflectionDirection(const IntersectionResult &ir) {

    float x,y,z;
    do {
        x = 2.0f*((float)rand())/RAND_MAX-1.0f;
        y = 2.0f*((float)rand())/RAND_MAX-1.0f;
        z = 2.0f*((float)rand())/RAND_MAX-1.0f;
    } while(x*x+y*y+z*z>1);

    Vector3 direction(x,y,z);

    if(direction.DotProduct(ir.intersectionPointNormal)<0)
        direction*=-1;

    return direction;
}

std::list<Stream*> StreamPhotonMap::GetClosestPhotons(Vector3 point, float radius, int maxPhotons) {
    return kdTree->FindClosest(point, radius, maxPhotons);
}
