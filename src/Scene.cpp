#include "Scene.h"
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include "Triangle.h"
#include "ObjFile.h"
#include "Sphere.h"
#include "Config.h"
#include "Utility.h"
#include <memory>
#include <iostream>
#include <random>

#include "materials/Lambertian.h"
#include "materials/Dielectric.h"
#include "materials/BeersLawMaterial.h"
#include "materials/BeersLawHeterogeneousMaterial.h"
#include "materials/SingleScatterHomogeneousMaterial.h"
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
        triangle->setTransform(ngl::Mat4::scale(5, 5, 5));
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
        triangle->setTransform(ngl::Mat4::translate(-1.0, -1.0, -1.0));
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
        triangle->setTransform(ngl::Mat4::translate(0.0, -1.0, -0.5));
        triangle->setMaterial(material);
    }
    scene.addObject(teaPotGroup);
}

void openBox1(Scene &scene, std::shared_ptr<Material> material)
{
    ObjFile box1("files/Box1.obj");
    auto gBox1 = box1.defaultGroup();
    for (auto t=0; t < gBox1->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(gBox1->getChildren()[t]);
        triangle->setMaterial(material);
        triangle->setTransform(ngl::Mat4::translate(1.5f, -2.0f, 1.5f));
        triangle->setTransform(ngl::Mat4::scale(2.0f, 3.5f, 2.0f));
        scene.addObject(triangle);
    }
}

void openBox2(Scene &scene, std::shared_ptr<Material> material)
{
    ObjFile box2("files/Box2.obj");
    auto gBox2 = box2.defaultGroup();
    for (auto t=0; t < gBox2->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(gBox2->getChildren()[t]);
        triangle->setMaterial(material);
        triangle->setTransform(ngl::Mat4::translate(-2.0f, -3.5f, -1.5f));
        triangle->setTransform(ngl::Mat4::scale(1.5f, 1.5f, 1.5f));
        scene.addObject(triangle);
    }
}

void openLight(Scene &scene, std::shared_ptr<Material> material)
{
    ObjFile box2("files/Box.obj");
    auto gBox2 = box2.defaultGroup();
    for (auto t=0; t < gBox2->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(gBox2->getChildren()[t]);
        triangle->setMaterial(material);
        triangle->setTransform(ngl::Mat4::translate(0.0f, 4.99f, 0.0f));
        triangle->setTransform(ngl::Mat4::scale(1.5f, 0.001f, 1.5f));
        scene.addObject(triangle);
    }
}

void Scene::chooseScene (SceneMode mode)
{
    auto materialBeers = std::make_shared<BeersLawMaterial>(ngl::Vec3(0.4, 0.4, 0.4));
    auto materialSingleScatterHomo = std::make_shared<SingleScatterHomogeneousMaterial>(ngl::Vec3(0.5, 0.5, 0.5), ngl::Vec3(0.5, 0.5, 0.5));
    auto materialHete = std::make_shared<BeersLawHeterogeneousMaterial>(0.5, 1);
    
    auto materialDielectric = std::make_shared<Dielectric>(-0.4);
    auto difflight = std::make_shared<LightEmitting>(ngl::Vec3(4,4,4));

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
        openBox1(*this, materialGray);
        openBox2(*this, materialGray);
        openLight(*this, difflight);
    }
    else if (mode == SceneMode::Scene2)
    {
        openTeapot(*this, materialCenter);
        auto s1 = std::make_shared<Sphere>(1, materialGray);
        s1->setTransform(ngl::Mat4::translate(0.0, -10, -1.0));
        s1->setTransform(ngl::Mat4::scale(100.0f, 1.0f, 100.0f));
        this->addObject(s1);
    }
    else if (mode == SceneMode::Scene3)
    {
        auto s1 = std::make_shared<Sphere>(1, materialGray);
        s1->setTransform(ngl::Mat4::translate(0.0, -100.5, -1.0));
        s1->setTransform(ngl::Mat4::scale(100.0f, 100.0f, 100.0f));
        this->addObject(s1);

        auto s2 = std::make_shared<Sphere>(2, materialBeers);
        s2->setTransform(ngl::Mat4::translate(0.0, 0.0, -1.0));
        s2->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
        this->addObject(s2);
        
        auto s3 = std::make_shared<Sphere>(3, materialRight);
        s3->setTransform(ngl::Mat4::translate(1.0f, 0.0f, -1.0f));
        s3->setTransform(ngl::Mat4::scale(0.5, 0.5, 0.5));
        m_objects.push_back(s3);

        openPyramid(*this, materialCenter);
    }
    else if (mode == SceneMode::Scene4)
    {
        openCornelBox(*this);
        openLight(*this, difflight);

        auto sphere = std::make_shared<Sphere>(1, materialLeft);
        sphere->setTransform(ngl::Mat4::translate(0.0f, -2.25f, 0.0f));
        sphere->setTransform(ngl::Mat4::scale(1.5, 1.5, 1.5));
        m_objects.push_back(sphere);
    }
    else if (mode == SceneMode::Scene5)
    {
        auto sphere = std::make_shared<Sphere>(1, materialHete);
        sphere->setTransform(ngl::Mat4::translate(0.0f, 1.0f, -2.5f));
        sphere->setTransform(ngl::Mat4::scale(2.0f, 2.0f, 2.0f));
        this->addObject(sphere);
        openFloor(*this);
    }
    else 
    {
        auto sphere = std::make_shared<Sphere>(1, materialBeers);
        sphere->setTransform(ngl::Mat4::translate(0.0f, 1.1f, 0.0f));
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

float Scene::softShadowFactor(const Computation &comp, int numSamples) 
{
    int unoccludedRays = 0;
    float totalTransmittance = 0.0f;

    for (int i = 0; i < numSamples; ++i) 
    {
        ngl::Vec4 samplePoint;
        ngl::Vec3 intensity; 
        m_areaLight.sample(samplePoint, intensity);

        auto [occluded, transmittance] = m_rs.computeTransmittance(comp.point, samplePoint, *this);
        if (!occluded) 
        {
            unoccludedRays++;
            totalTransmittance += transmittance.length();
        }
    }

    return (static_cast<float>(unoccludedRays) / numSamples) * (totalTransmittance / numSamples);
}


ngl::Vec3 Scene::directLighting(const Computation& comp) 
{
    RendererServices rs = m_rs; 
    ngl::Vec3 directLight(0.0, 0.0, 0.0);

    // generate a sample based on the light
    ngl::Vec3 Ll;
    ngl::Vec4 sampledDirLight;
    float pdfLight;
    ngl::Vec3 beamTransmittance;
    rs.generateLightSample(comp, sampledDirLight, Ll, pdfLight, beamTransmittance, *this);
    float shadowFactor = softShadowFactor(comp, NUM_LIGHT_SAMPLES);
    if (shadowFactor <= 0.0f) 
    {
        return directLight;
    }
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
        rs.evaluateLightSample(comp, sampledDirMaterial, fr, pdfLight, beamTransmittance, *this);
        auto [occluded, transmittance] = m_rs.computeTransmittance(comp.point, comp.point + sampledDirMaterial, *this);
        beamTransmittance = beamTransmittance * transmittance;
        if (pdfLight > 0.0f && !comp.matPtr->hasVolume()) 
        {
            float weight = rs.MISWeight(SAMPLES_PER_PIXEL, pdfMaterial, 1, pdfLight);
            directLight += fr * Lm * beamTransmittance * weight / (pdfLight + 1e-6f);;
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
        LightEmitting* leMaterial = dynamic_cast<LightEmitting*>(m.get()); 
        if (leMaterial) {
            L += throughput * leMaterial->albedo().toVec3();
        }


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
            if (!volume->integrate(nextRay, Lv, transmittance, weight, ctx.point, nextRay, *ctx.object, m_rs, *this)) break;
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