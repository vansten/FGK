#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "AmbientLight.h"

class Scene;

class PointLight : public AmbientLight
{
public:
    PointLight();
    /**
      Constructs point light with given position, color and attenuation parameters
      */
    PointLight(Vector3 position, Color color, Vector3 attenuation);
    ~PointLight();

    LightIntensity GetLightIntensity(Vector3 cameraPosition, IntersectionResult *ir, std::list<Geometry*> &geometry);

    /**
      Gets position of light
      */
    Vector3 GetPosition() const;
    Ray GetPhoton(bool useProjectionMap=false) const;

    void CreateProjectionMap(const Scene* scene);

    float GetProjectionMapRatio() const;

protected:
    virtual bool IsInShadow(IntersectionResult *ir, std::list<Geometry *> &geometry);

private:
    Vector3 position;
    Vector3 attenuation;

    Texture* projectionMap;
};

#endif // POINTLIGHT_H
