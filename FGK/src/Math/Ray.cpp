#include "Ray.h"
#include "Plane.h"

Ray::Ray(void)
{
    origin = Vector3(0,0,0);
    direction = Vector3(0,0,1);
}

Ray::Ray(const Vector3 &orig, const Vector3 &dir) : origin(orig), direction(dir) {
    direction.Normalize();
}