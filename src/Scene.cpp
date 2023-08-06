#include "Scene.h"
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include "Triangle.h"
#include "ObjFile.h"
#include "Sphere.h"
#include "Utility.h"
#include "RendererServices.h"
#include <memory>
#include <iostream>
#include <random>

#include "materials/Lambertian.h"
#include "materials/Dielectric.h"
#include "materials/BeersLawMaterial.h"
#include "materials/BeersLawHeterogeneousMaterial.h"
#include "materials/SingleScatterHomogeneousMaterial.h"
#include "materials/SingleScatterHeterogeneousMaterial.h"
#include "materials/LightEmitting.h"
#include "materials/Metal.h"

Scene::Scene(bool _default)
{
    if(_default) 
    {
        auto lPoint = ngl::Vec4(-10.0f, 10.0f, 10.0f);
        auto lIntensity = ngl::Vec3(1.0f,1.0f,1.0f);
        auto l = Light(lIntensity,lPoint);
        m_light = l;

        auto s1 = std::make_shared<Sphere>(1);
        auto mColor = ngl::Vec3(0.8f,1.0f,0.6f);
        m_objects.push_back(s1);

        auto s2 = std::make_shared<Sphere>(2);
        auto transform = ngl::Mat4::scale(0.5f,0.5f,0.5f);
        s2->setTransform(transform);
        m_objects.push_back(s2);
    }

}

void openCornelBox (Scene &scene)
{
    auto materialGreen = std::make_shared<Lambertian>(ngl::Vec4(0.0, 1.0, 0.0));
    auto materialRed = std::make_shared<Lambertian>(ngl::Vec4(1.0, 0.0, 0.0));
    auto materialWhite = std::make_shared<Lambertian>(ngl::Vec4(1.0, 1.0, 1.0 ));

    std::shared_ptr<Lambertian> cornelBoxMaterial[3] = {materialGreen, materialRed, materialWhite};

    ObjFile cornellBox("files/CornellBox.obj");
    auto cornellBoxGroup = cornellBox.defaultGroup();
    auto mIdx = 0;
    for (auto t=0; t < cornellBoxGroup->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(cornellBoxGroup->getChildren()[t]);
        triangle->setMaterial(cornelBoxMaterial[mIdx]);
        scene.addObject(triangle);
        if (mIdx < 2 && t % 2 == 1) 
        {
            mIdx++;
        }
    }
}

void openFloor (Scene &scene)
{
    auto materialGreen = std::make_shared<Lambertian>(ngl::Vec4(0.0, 1.0, 0.0));
    auto materialRed = std::make_shared<Lambertian>(ngl::Vec4(1.0, 0.0, 0.0));
    auto materialWhite = std::make_shared<Lambertian>(ngl::Vec4(1.0, 1.0, 1.0 ));
    auto materialBlue = std::make_shared<Lambertian>(ngl::Vec4(0.0, 0.0, 1.0 ));


    std::shared_ptr<Lambertian> floorMaterial[4] = {materialGreen, materialRed, materialWhite, materialBlue};

    ObjFile floor("files/Floor.obj");
    auto floorGroup = floor.defaultGroup();
    auto mIdx = 0;
    for (auto t=0; t < floorGroup->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(floorGroup->getChildren()[t]);
        triangle->setMaterial(floorMaterial[mIdx]);
        triangle->setTransform(ngl::Mat4::scale(100, 1, 100));
        scene.addObject(triangle);
        if (t % 2 == 1) 
        {
            mIdx++;
        }
    }
}

void openPyramid (Scene &scene, std::shared_ptr<Material> material)
{
    ObjFile pyramid("files/Pyramid.obj");
    auto pyramidGroup = pyramid.defaultGroup();
    for (auto t=0; t < pyramidGroup->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(pyramidGroup->getChildren()[t]);
        triangle->setMaterial(material);
        triangle->setTransform(ngl::Mat4::translate(0, -1.0, -1.0));
        // triangle->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
        scene.addObject(triangle);
    }
}

void openTeapot(Scene &scene, std::shared_ptr<Material> material)
{
    ObjFile teaPot("files/Teapot.obj");
    auto teaPotGroup = teaPot.defaultGroup();
    for (auto t=0; t < teaPotGroup->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(teaPotGroup->getChildren()[t]);
        triangle->setTransform(ngl::Mat4::translate(0.0, -0.5, -0.5));
        // triangle->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
        triangle->setMaterial(material);
    }
    scene.addObject(teaPotGroup);
}

void openBox1(Scene &scene, std::shared_ptr<Material> material)
{
    ObjFile box1("files/Box.obj");
    auto gBox1 = box1.defaultGroup();
    for (auto t=0; t < gBox1->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(gBox1->getChildren()[t]);
        triangle->setMaterial(material);
        triangle->setTransform(ngl::Mat4::translate(-0.5f, -0.5f, 0.5f));
        triangle->setTransform(ngl::Mat4::scale(0.3f, 0.6f, 0.3f));
        scene.addObject(triangle);
    }
}

void openBox2(Scene &scene, std::shared_ptr<Material> material)
{
    ObjFile box2("files/Box.obj");
    auto gBox2 = box2.defaultGroup();
    for (auto t=0; t < gBox2->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(gBox2->getChildren()[t]);
        triangle->setMaterial(material);
        triangle->setTransform(ngl::Mat4::translate(0.4f, -0.7f, 0.0f));
        triangle->setTransform(ngl::Mat4::scale(0.3f, 0.3f, 0.3f));
        scene.addObject(triangle);
    }
}

void Scene::chooseScene (SceneMode mode)
{
    auto materialGround = std::make_shared<Lambertian>(ngl::Vec4(0.8, 0.8, 0.0));
    auto materialBack = std::make_shared<Lambertian>(ngl::Vec4(0.5, 0.7, 1.0));
    auto materialBeers = std::make_shared<BeersLawMaterial>(ngl::Vec3(0.8, 0.8, 0.8));
    auto materialSingleScatterHomo = std::make_shared<SingleScatterHomogeneousMaterial>(ngl::Vec3(0.2, 0.2, 0.2), ngl::Vec3(0.01, 0.01, 0.01));
    // auto materialSingleScatterHete = std::make_shared<SingleScatterHeterogeneousMaterial>(ngl::Vec3(0.2, 0.2, 0.2), ngl::Vec3(0.2, 0.2, 0.2), 1);

    auto materialHete = std::make_shared<BeersLawHeterogeneousMaterial>(0.5, 1);
    auto materialDielectric = std::make_shared<Dielectric>(-0.4);
    auto difflight = std::make_shared<LightEmitting>(ngl::Vec3(4,4,4));
    auto difflight2 = std::make_shared<LightEmitting>(ngl::Vec3(5,5,5));

    auto materialGreen = std::make_shared<Lambertian>(ngl::Vec4(0.0, 1.0, 0.0));
    auto materialRed = std::make_shared<Lambertian>(ngl::Vec4(1.0, 0.0, 0.0));
    auto materialWhite = std::make_shared<Lambertian>(ngl::Vec4(1.0, 1.0, 1.0 ));
    auto materialGray = std::make_shared<Lambertian>(ngl::Vec4(0.45, 0.45, 0.45));

    auto materialCenter = std::make_shared<Lambertian>(ngl::Vec4(0.7, 0.3, 0.3));
    auto materialLeft   = std::make_shared<Metal>(ngl::Vec4(0.8, 0.8, 0.8));
    auto materialRight  = std::make_shared<Metal>(ngl::Vec4(0.8, 0.6, 0.2));

    if (mode == SceneMode::Scene1)
    {
        openCornelBox(*this);
        // openTeapot(*this, materialCenter);
        openBox1(*this, materialGray);
        openBox2(*this, materialGray);
        // auto s4 = std::make_shared<Sphere>(4, materialSingleScatterHomo);
        // s4->setTransform(ngl::Mat4::translate(0.0f, -0.5f, -0.8f));
        // s4->setTransform(ngl::Mat4::scale(0.5, 0.5, 0.5));
        // m_objects.push_back(s4);
    }
    else if (mode == SceneMode::Scene2)
    {
        openPyramid(*this, materialBeers);
        openFloor(*this);
    }
    else if (mode == SceneMode::Scene3)
    {
        openTeapot(*this, materialCenter);
    }
    else if (mode == SceneMode::Scene4)
    {
        auto s1 = std::make_shared<Sphere>(1, materialGround);
        s1->setTransform(ngl::Mat4::translate(0.0, -100.5, -1.0));
        s1->setTransform(ngl::Mat4::scale(100.0f, 100.0f, 100.0f));
        this->addObject(s1);

        auto s3 = std::make_shared<Sphere>(3, materialCenter);
        s3->setTransform(ngl::Mat4::translate(0.0, 0.0, -1.0));
        s3->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
        this->addObject(s3);
        
        auto s4 = std::make_shared<Sphere>(4, materialRight);
        s4->setTransform(ngl::Mat4::translate(1.0f, 0.0f, -1.0f));
        s4->setTransform(ngl::Mat4::scale(0.5, 0.5, 0.5));
        m_objects.push_back(s4);

        openPyramid(*this, materialRight);
    }
    else 
    {
        auto sphere = std::make_shared<Sphere>(1, materialHete);
        sphere->setTransform(ngl::Mat4::translate(0.0f, 1.0f, -3.0f));
        sphere->setTransform(ngl::Mat4::scale(2.0f, 2.0f, 2.0f));
        this->addObject(sphere);
        openFloor(*this);
    }
}

std::vector<std::shared_ptr<Shape>>& Scene::objects()
{
    return m_objects;
}

AreaLight Scene::areaLight() const
{
    return m_areaLight;
}

void Scene::areaLight(AreaLight _l)
{
    m_areaLight = _l;
}

RendererServices Scene::rs() const
{
    return m_rs;
}

void Scene::rs(RendererServices _rs)
{
    m_rs = _rs;
}


Light Scene::light() const
{
    return m_light;
}

void Scene::light(Light _l)
{
    m_light = _l;
}

void Scene::addObject(std::shared_ptr<Shape> s)
{
    m_objects.push_back(s);
}

std::vector<Intersection> Scene::intersectScene(Ray _r)
{
    std::vector<Intersection> intersections;
    for (const auto& o : m_objects)
    {
        auto inter = o->intersect(_r);
        for(auto &i: inter)
            intersections.push_back(i);
    }
    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) 
    {
        return a.t() < b.t();
    });
    return intersections;
}

// ngl::Vec3 Scene::shadeHit(Computation _c)
// {
//     auto m =  _c.object->oldMaterial();
//     return m.lighting(this->light(), _c.point, _c.eye, _c.normal);
// }

ngl::Vec3 Scene::colorAt(Ray _r, int depth)
{
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return ngl::Vec3(0,0,0);
    
    auto intersections = this->intersectScene(_r);
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    Intersection empty = Intersection();
    if (i == empty)
    {
        auto d = _r.direction()/_r.direction().length();
        auto t = 0.5 * (d.m_y + 1.0);
        auto color = (1.0-t)*ngl::Vec3(1.0, 1.0, 1.0) + t*ngl::Vec3(0.5, 0.7, 1.0);    
        return color;
    }
    else
    {
        auto c = i.prepareComputations(_r);

        Ray scattered;
        ngl::Vec3 attenuation;
        // if (c.matPtr && c.matPtr->scatter(_r, c, attenuation, scattered))
        //     return attenuation * colorAt(scattered, depth-1);
        // return ngl::Vec3(0.0f,0.0f,0.0f);
        // return shadeHit(c);
    }
}

// bool Scene::isOccluded(const ngl::Vec4 &start, const ngl::Vec4 &end) 
// {
//     auto direction = end - start;
//     float distance = direction.length();
//     direction.normalize();
    
//     // Create a ray from start towards direction
//     ngl::Vec4 offsetStart = start + 0.001f * direction; // Offset by a small amount
//     Ray shadowRay(offsetStart, direction);
    
//     // For each object in the scene
//     auto intersections = this->intersectScene(shadowRay);
//     auto xs = Intersection::intersections(intersections);
//     auto i = Intersection::hit(xs);

//     if (i != Intersection())
//     {
//         return true;
//     }
//     return false;
// }

std::pair<bool, float> Scene::computeTransmittance(const ngl::Vec4 &start, const ngl::Vec4 &end)
{
    auto direction = end - start;
    float distance = direction.length();
    direction.normalize();

    ngl::Vec4 offsetStart = start + 0.001f * direction;
    Ray shadowRay(offsetStart, direction);

    auto intersections = this->intersectScene(shadowRay);
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    float transmittance = 1.0f; 
    if (i != Intersection())
    {
        // This is where you'll need to compute the transmittance based on the volume's properties.
        // This can be a function of the volume's density, the distance the ray travels within the volume, etc.
        // For now, let's assume a simple exponential attenuation:
        // transmittance = exp(-volumeDensity * distance);

        // NOTE: You'll need more logic here to determine the correct volume and its properties.
        auto comp = i.prepareComputations(shadowRay);
        auto m = comp.matPtr;
        if (m->hasVolume()) 
        {
            float dirDotN = shadowRay.direction().dot(comp.normal);
            bool entered = dirDotN < 0.0f;
            if (entered) {
                shadowRay.enterMaterial(m);
            } else {
                shadowRay.exitMaterial(m);
            }
            auto volume = shadowRay.getVolume(comp);
            // Store the entry point
            ngl::Vec4 P0 = comp.point;

            // Continue tracing from P0 to find the exit point
            ngl::Vec4 offsetP0 = P0 + 0.001f * direction;
            Ray continueRay(offsetP0, direction);
            auto nextIntersections = this->intersectScene(continueRay);
            auto nextHits = Intersection::intersections(nextIntersections);
            auto nextI = Intersection::hit(nextHits);

            ngl::Vec4 P1;
            if (nextI != Intersection())
            {
                auto compI = nextI.prepareComputations(shadowRay);
                P1 = compI.point;
            }
            else
            {
                return {i != Intersection(), transmittance};
                // Handle the case where there's no exit point. Could be a max distance or special case.
            }

            // Compute transmittance using P0 and P1
            if(volume != nullptr)
                transmittance = volume->transmittance(P0, P1).length();
                    
        }
    }
    return {i != Intersection(), transmittance};
}

float Scene::softShadowFactor(const Computation &comp, int numSamples) 
{
    int unoccludedRays = 0;
    float totalTransmittance = 0.0f;

    for (int i = 0; i < numSamples; ++i) 
    {
        ngl::Vec4 samplePoint;
        ngl::Vec3 intensity; 
        m_areaLight.sample(samplePoint, intensity);

        auto [occluded, transmittance] = computeTransmittance(comp.point, samplePoint);
        if (!occluded) 
        {
            unoccludedRays++;
            totalTransmittance += transmittance;
        }
    }

    // We'll average the transmittance of all the rays to get a soft shadow effect.
    return (static_cast<float>(unoccludedRays) / numSamples) * (totalTransmittance / numSamples);
}

ngl::Vec3 Scene::directLighting(const Computation& comp) 
{
    RendererServices rs = m_rs;  // assuming you have a vector of lights named areaLights
    ngl::Vec3 directLight(0.0, 0.0, 0.0);

    // generate a sample based on the light
    ngl::Vec3 Ll;
    ngl::Vec4 sampledDirLight;
    float pdfLight;
    ngl::Vec3 beamTransmittance;
    rs.generateLightSample(comp, sampledDirLight, Ll, pdfLight, beamTransmittance);
    float shadowFactor = softShadowFactor(comp, NUM_LIGHT_SAMPLES);
    if (shadowFactor <= 0.0f) 
    {
        return directLight;
    }
    // if (isOccluded(comp.point, comp.point + sampledDirLight)) 
    // {
    //     return directLight;
    // }
    if (pdfLight > 0.0f) 
    {
        // compute contribution to directLight from the light sample
        ngl::Vec3 fr;
        float pdfMaterial;
        auto m = comp.matPtr;
        auto bsdf = m->createBSDF(comp);
        bsdf->evaluateSample(comp, sampledDirLight, fr, pdfMaterial);

        if (pdfMaterial > 0.0f) 
        {
            float weight = rs.MISWeight(1, pdfLight, SAMPLES_PER_PIXEL, pdfMaterial);

            directLight += shadowFactor * fr * Ll * beamTransmittance * std::abs(comp.normal.dot(sampledDirLight.toVec3())) * weight / pdfLight;
            // directLight += fr * Ll * beamTransmittance * std::abs(comp.normal.dot(sampledDirLight.toVec3())) * weight / pdfLight;

        }
    }

    ngl::Vec3 Lm;
    ngl::Vec4 sampledDirMaterial;
    float pdfMaterial;
    auto m = comp.matPtr;
    auto bsdf = m->createBSDF(comp);
    bsdf->generateSample(comp, sampledDirMaterial, Lm, pdfMaterial);
    if (pdfMaterial > 0.0f) 
    {
        ngl::Vec3 fr;
        float pdfLight;
        ngl::Vec3 beamTransmittance;
        rs.evaluateLightSample(comp, sampledDirMaterial, fr, pdfLight, beamTransmittance);

        if (pdfLight > 0.0f) 
        {
            float weight = rs.MISWeight(SAMPLES_PER_PIXEL, pdfMaterial, 1, pdfLight);
            directLight += fr * Ll * beamTransmittance * std::abs(comp.normal.dot(sampledDirLight.toVec3())) * weight / (pdfLight + 1e-6f);;
        }
    }

    return directLight;
}

ngl::Vec3 Scene::pathTrace(const Ray& r, int maxDepth) 
{
    ngl::Vec3 L(0,0,0);
    ngl::Vec3 throughput(1.0, 1.0, 1.0);
    Ray ray = r;
    for (int j = 0; j < maxDepth; ++j) 
    {
        auto intersections = this->intersectScene(ray);
        auto xs = Intersection::intersections(intersections);
        auto i = Intersection::hit(xs);

        Intersection empty = Intersection();
        if (i == empty)
        {
            break;
        }

        auto ctx = i.prepareComputations(ray);

        auto m = ctx.matPtr;
        auto bsdf = m->createBSDF(ctx);

        L += throughput * directLighting(ctx);

        // Sample direction for next ray from BSDF
        float pdf;
        ngl::Vec3 Ls;
        ngl::Vec4 sampleDirection;
        bsdf->generateSample(ctx, sampleDirection, Ls, pdf);

        throughput = throughput * (Ls / pdf);

        Ray nextRay(ctx.point, sampleDirection);

        std::shared_ptr<Volume> volume = nullptr;
        if (m->hasVolume()) {

            auto EyedotN = ctx.eye.dot(ctx.normal);
            auto dirDotN = sampleDirection.dot(ctx.normal.toVec3());
            auto transmit = (EyedotN < 0.0) != (dirDotN < 0.0);
            if (transmit) {
                // We transmitted through the surface. Check dot product between the sample direction and the
                // surface normal N to see whether we entered or exited the volume media
                bool entered = dirDotN < 0.0f;
                if (entered) {
                    nextRay.enterMaterial(m);
                } else {
                    nextRay.exitMaterial(m);
                }
            }
            volume = nextRay.getVolume(ctx);
        }
        if (volume) {
            ngl::Vec3 Lv;
            ngl::Vec3 transmittance;
            ngl::Vec3 weight;
            if (!volume->integrate(nextRay, Lv, transmittance, weight, ctx.point, nextRay, *ctx.object, m_rs)) break;
            L += weight * throughput * Lv;
            throughput = throughput * transmittance;
        } else {
            auto intersections = this->intersectScene(nextRay);
            auto xs = Intersection::intersections(intersections);
            auto i = Intersection::hit(xs);

            Intersection empty = Intersection();
            if (i == empty)
            {
                break;
            }
        }
        ray = nextRay;
    }

    return L;
}