#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene() {
	auto geometryIt = geometry.begin();
	auto geometryEnd = geometry.end();
	for(geometryIt; geometryIt != geometryEnd; ++geometryIt)
	{
		delete (*geometryIt);
	}

	auto lightsIt = lights.begin();
	auto lightsEnd = lights.end();
	for(lightsIt; lightsIt != lightsEnd; ++lightsIt)
	{
		delete (*lightsIt);
	}

	geometry.clear();
	lights.clear();
}
