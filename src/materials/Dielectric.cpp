#include "materials/Dielectric.h"

Dielectric::Dielectric(float index_of_refraction) {
    m_ir = index_of_refraction;
}

bool Dielectric::hasVolume() {
    return false;
}

std::shared_ptr<BSDF> Dielectric::createBSDF(const Computation& _comp) {
    return std::make_shared<DielectricBSDF>(_comp, m_ir);
}
