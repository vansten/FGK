#ifndef AREALIGHT_H
#define AREALIGHT_H
#include <vector>
#include "AmbientLight.h"
#include "../Math/Vector2.h"
#include "PointLight.h"

class AreaLight : public AmbientLight
{
public:
    /**
      Creates array of point lights, with given center and size.
      All lights in array have the same color and attenuation
      */
    AreaLight(Vector3 center, Vector2 size, Color color, Vector3 attenuation, int density);
    ~AreaLight();

    virtual LightIntensity GetLightIntensity(Vector3 cameraPosition, IntersectionResult *ir, std::list<Geometry *> &geometry);
    Ray GetPhoton(bool useProjectionMap=false) const;
    void CreateProjectionMap(const Scene* scene);
    float GetProjectionMapRatio() const;

protected:
    bool IsInShadow(IntersectionResult *ir, std::list<Geometry *> &geometry);
private:
	std::vector<PointLight*> lights;
	std::vector<bool> inShadows;
    Vector3 center;
    Vector2 size;
};

#endif // AREALIGHT_H
