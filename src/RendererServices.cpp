#include "RendererServices.h"
#include "Material.h"
#include "Volume.h"

RendererServices::RendererServices(AreaLight _light) : m_light(_light)
{
}


float RendererServices::MISWeight(int nsamps1, float pdf1, int nsamps2, float pdf2) {
    float s1 = nsamps1 * pdf1;
    float s2 = nsamps2 * pdf2;
    return s1 / (s1 + s2);
}

void RendererServices::GenerateLightSample(const Computation &_comp, ngl::Vec4 &sampleDirection, ngl::Vec3 &L, float &pdf, ngl::Vec3 &beamTransmittance) 
{
    
    // Compute SampleDirection
    ngl::Vec4 samplePoint;
    m_light.sample(samplePoint, L);
    ngl::Vec4 lightToSurface = samplePoint - _comp.point;
    lightToSurface.normalize();
    sampleDirection = lightToSurface;

    // Compute pdf
    float lightArea = m_light.udir().length() * m_light.vdir().length();
    float distanceSquared = lightToSurface.lengthSquared();

    auto normalToLightPlane = m_light.udir().cross(m_light.vdir());
    normalToLightPlane.normalize();

    pdf = distanceSquared / (lightArea * std::abs(sampleDirection.dot(normalToLightPlane)));

    // Compute beamTransmittance
    if(_comp.matPtr->hasVolume()) {
        Computation comp = _comp;
        auto volume = _comp.incomingRay.getVolume(comp);
        beamTransmittance = volume->transmittance(_comp.point, samplePoint);
    } else {
        beamTransmittance = ngl::Vec3(1.0f, 1.0f, 1.0f);
    }
}

void RendererServices::EvaluateLightSample(const Computation &_comp, const ngl::Vec4 &sampleDirection, ngl::Vec3 &L, float &pdf, ngl::Vec3 &beamTransmittance)
{
    // Compute L using BSDF and incident direction.
    auto m = _comp.matPtr;
    auto bsdf = m->createBSDF(_comp);

    ngl::Vec3 evaluatedColor;
    bsdf->evaluateSample(_comp, sampleDirection, evaluatedColor, pdf);
    L = evaluatedColor;

    // Compute pdf
    if (sampleDirection.dot(_comp.normal) > 0) {
        float lightArea = m_light.udir().length() * m_light.vdir().length();
        float distanceSquared = (m_light.center() - _comp.point).lengthSquared();
        auto normalToLightPlane = m_light.udir().cross(m_light.vdir());
        normalToLightPlane.normalize();
        pdf = distanceSquared / (lightArea * std::abs(sampleDirection.dot(normalToLightPlane)));
    } else {
        pdf = 0.0f;
    }

    // Compute beamTransmittance
    if(_comp.matPtr->hasVolume()) {
        Computation comp = _comp;
        auto volume = _comp.incomingRay.getVolume(comp);
        beamTransmittance = volume->transmittance(_comp.point, m_light.center());
    } else {
        beamTransmittance = ngl::Vec3(1.0f, 1.0f, 1.0f);
    }
}

void RendererServices::EvaluateLightSample(const Computation &_comp, const ngl::Vec3 &sampleDirection, ngl::Vec3 &L, float &pdf)
{
    // // Compute L using BSDF and incident direction.
    // auto m = _comp.matPtr;
    // auto bsdf = m->createBSDF(_comp);

    // ngl::Vec3 evaluatedColor;
    // bsdf->evaluateSample(_comp, sampleDirection, evaluatedColor, pdf);
    // L = evaluatedColor;

    // // The beamTransmittance calculation is omitted in this method signature.
}
