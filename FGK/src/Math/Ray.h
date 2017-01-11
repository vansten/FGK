#ifndef RAY_H
#define RAY_H

#include "Vector3.h"
class Geometry;

class Ray
{
public:
    Vector3 origin;
    Vector3 direction;

    Ray(void);
    Ray(const Vector3& orig, const Vector3& dir);    

	inline std::string ToString() const
	{
		return "Origin: " + origin.ToString() + ", direction: " + direction.ToString();
	}
};

enum IntersectionType {
    MISS = 0,
    HIT,
    INSIDE_PRIMITIVE
};

struct IntersectionResult {
    IntersectionResult() {
        type=MISS;
        object=0;
    }

    IntersectionResult(IntersectionType t,
                       Vector3 p,
                       Vector3 n,
                       float dist) : type(t), point(p),
                                     intersectionPointNormal(n), distance(dist) {}

	inline std::string ToString() const
	{
		if(type == MISS)
		{
			return "No intersection";
		}
		else if(type==HIT)
		{
			return "Intersection at point: " + point.ToString() + ", distance" + std::to_string(distance) + ", normal: " + intersectionPointNormal.ToString();
		}
		else 
		{
			return "Intersection at point: " + point.ToString() + ", distance" + std::to_string(distance) + ", normal: " + intersectionPointNormal.ToString();
		}
	}

    IntersectionType type;
    Vector3 point;
    Vector3 intersectionPointNormal;
    float distance;
    const Geometry* object;
};


#endif // RAY_H
