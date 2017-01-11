#include "AmbientLight.h"

AmbientLight::AmbientLight() {
    type = LightSourceType::AMBIENT;
    color = Color(1,1,1);
}

AmbientLight::AmbientLight(Color c) : color(c) {
    type = LightSourceType::AMBIENT;
}

bool AmbientLight::IsInShadow(IntersectionResult*, std::list<Geometry *>&) {
    return false;
}

LightIntensity AmbientLight::GetLightIntensity(Vector3 cameraPosition, IntersectionResult *ir, std::list<Geometry *> &geometry) {
    return color;
}

Ray AmbientLight::GetPhoton(bool useProjectionMap) const {
    return Ray();
}

void AmbientLight::CreateProjectionMap(const Scene *s) {

}

float AmbientLight::GetProjectionMapRatio() const {
    return 0;
}
