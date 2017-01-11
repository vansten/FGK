#ifndef SCENE_H
#define SCENE_H
#include <list>
#include "Lights/AmbientLight.h"
#include "Geometry/Geometry.h"

/**
  Represents scene that we want to render.
  Contains all geometry and light.
  */
class Scene
{
public:
    Scene();
    ~Scene();

    /**
      Adds geometry to scene
      */
    void AddGeometry(Geometry*g) {
		geometry.push_back(g);
    }

    /**
      Adds light to scene
      */
    void AddLight(AmbientLight* l) {
		lights.push_back(l);
    }

	std::list<Geometry*> geometry;
	std::list<AmbientLight*> lights;
};

#endif // SCENE_H
