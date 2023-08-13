#include "materials/Dielectric.h"

// Constructor initializes the dielectric material with a specified index of refraction.
Dielectric::Dielectric(float index_of_refraction) : m_ir(index_of_refraction) {}

// Dielectrics are considered to be non-volumetric in this context.
bool Dielectric::hasVolume() 
{
    return false;
}

// Creates a DielectricBSDF for light interactions with this dielectric material.
std::shared_ptr<BSDF> Dielectric::createBSDF(const Computation& _comp) 
{
    return std::make_shared<DielectricBSDF>(_comp, m_ir);
}
