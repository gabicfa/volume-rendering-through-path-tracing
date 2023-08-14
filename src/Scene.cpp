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

    auto materialHete = std::make_shared<BeersLawHeterogeneousMaterial>(0.5);
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

// Retrieve all objects present in the scene.
std::vector<std::shared_ptr<Shape>>& Scene::objects()
{
    return m_objects;
}

// Retrieve the current area light of the scene.
AreaLight Scene::areaLight() const
{
    return m_areaLight;
}

// Set the area light of the scene.
void Scene::areaLight(AreaLight _l)
{
    m_areaLight = _l;
}

// Retrieve the renderer services.
RendererServices Scene::rs() const
{
    return m_rs;
}

// Set the renderer services.
void Scene::rs(RendererServices _rs)
{
    m_rs = _rs;
}

// Retrieve the light of the scene.
Light Scene::light() const
{
    return m_light;
}

// Set the light of the scene.
void Scene::light(Light _l)
{
    m_light = _l;
}

// Add a shape to the scene.
void Scene::addObject(std::shared_ptr<Shape> s)
{
    m_objects.push_back(s);
}

// Find intersections of a ray with all objects in the scene.
std::vector<Intersection> Scene::intersectScene(Ray _r)
{
    std::vector<Intersection> intersections;
    for (const auto& o : m_objects)
    {
        auto inter = o->intersect(_r);
        for(auto &i: inter)
            intersections.push_back(i);
    }

    // Sort intersections based on distance from ray origin.
    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) 
    {
        return a.t() < b.t();
    });

    return intersections;
}

// Compute factor for soft shadow based on the number of unoccluded rays.
float Scene::softShadowFactor(const Computation &comp, int numSamples) 
{
    int unoccludedRays = 0;
    float totalTransmittance = 0.0f;
    for (int i = 0; i < numSamples; ++i) 
    {
        // Variables to store the sample point on the light and the intensity of the light at that sample point.
        ngl::Vec4 samplePoint;
        ngl::Vec3 intensity; 
        
        // Sample a point on the area light.
        m_areaLight.sample(samplePoint, intensity);

        // Compute the transmittance of light between the computation point and the sampled point on the light.
        // If occluded is true, the light path between comp.point and samplePoint is blocked by some object.
        auto [occluded, transmittance] = m_rs.computeTransmittance(comp.point, samplePoint, *this);
        
        // If the light ray isn't blocked, update our counters.
        if (!occluded) 
        {
            unoccludedRays++;
            totalTransmittance += transmittance.length();
        }
    }

    // The final soft shadow factor is a combination of:
    // - The percentage of unoccluded rays.
    // - The average transmittance of all the unoccluded rays.
    return (static_cast<float>(unoccludedRays) / numSamples) * (totalTransmittance / numSamples);
}

// Compute the direct lighting at a computation point in the scene.
// This is achieved by sampling light sources and the surface material.
// The method takes into account the influence of shadows and multiple importance sampling (MIS) for better integration.
ngl::Vec3 Scene::directLighting(const Computation& comp) 
{
    RendererServices rs = m_rs; 
    ngl::Vec3 directLight(0.0, 0.0, 0.0);

    ngl::Vec3 Ll;
    ngl::Vec4 sampledDirLight;
    float pdfLight;
    ngl::Vec3 beamTransmittance;

    // Generate a sample direction based on the light source.
    rs.generateLightSample(comp, sampledDirLight, Ll, pdfLight, beamTransmittance, *this);
    
    // Calculate how much of the light is shadowed.
    float shadowFactor = softShadowFactor(comp, NUM_LIGHT_SAMPLES);
    
    // If the computation point is fully shadowed, return early.
    if (shadowFactor <= 0.0f) 
    {
        return directLight;
    }

    // If there's a valid probability of sampling the light, compute its contribution.
    if (pdfLight > 0.0f) 
    {
        ngl::Vec3 fr;
        float pdfMaterial;
        auto m = comp.matPtr;
        auto bsdf = m->createBSDF(comp);
        
        // Evaluate the surface material based on the light sample.
        bsdf->evaluateSample(comp, sampledDirLight, fr, pdfMaterial);

        // If there's a valid probability of sampling the material, calculate its contribution.
        if (pdfMaterial > 0.0f) 
        {
            float weight = rs.MISWeight(1, pdfLight, SAMPLES_PER_PIXEL, pdfMaterial);

            // Calculate the direct lighting contribution based on the surface material, light, and MIS weight.
            directLight += shadowFactor * fr * Ll * beamTransmittance * std::abs(comp.normal.dot(sampledDirLight.toVec3())) * weight / pdfLight;
        }
    }

    // Variables for sampled direction based on the material, emitted light, and pdf value.
    ngl::Vec3 Lm;
    ngl::Vec4 sampledDirMaterial;
    float pdfMaterial;
    
    auto m = comp.matPtr;
    auto bsdf = m->createBSDF(comp);
    
    // Generate a sample direction based on the surface material.
    bsdf->generateSample(comp, sampledDirMaterial, Lm, pdfMaterial);
    
    if (pdfMaterial > 0.0f) 
    {
        ngl::Vec3 fr;
        float pdfLight;
        ngl::Vec3 beamTransmittance;

        // Evaluate the light based on the material sample.
        rs.evaluateLightSample(comp, sampledDirMaterial, fr, pdfLight, beamTransmittance, *this);
        
        auto [occluded, transmittance] = m_rs.computeTransmittance(comp.point, comp.point + sampledDirMaterial, *this);
        beamTransmittance = beamTransmittance * transmittance;
        
        if (pdfLight > 0.0f && !comp.matPtr->hasVolume()) 
        {
            float weight = rs.MISWeight(SAMPLES_PER_PIXEL, pdfMaterial, 1, pdfLight);
            
            // Update the direct lighting contribution based on the material's sample.
            directLight += fr * Lm * beamTransmittance * weight / (pdfLight + 1e-6f);
        }
    }

    return directLight;
}

// Path-tracing algorithm: This function recursively traces a ray through the scene, bouncing off surfaces and accumulating light.
// The method considers direct lighting, emitted light from surfaces, and media (volumes) to simulate global illumination.
ngl::Vec3 Scene::pathTrace(const Ray& r, int maxDepth) 
{
    // Accumulator for the computed color/lighting along the ray.
    ngl::Vec3 L(0, 0, 0);
    
    // Represents the amount of light transmitted along the ray's path (starts fully unoccluded).
    ngl::Vec3 throughput(1.0, 1.0, 1.0);
    
    // Initialize with the camera ray.
    Ray ray = r;
    
    for (int j = 0; j < maxDepth; ++j) 
    {
        // Check if ray intersects any object in the scene.
        auto intersections = this->intersectScene(ray);
        auto xs = Intersection::intersections(intersections);
        auto i = Intersection::hit(xs);

        // If no intersection is found, the ray doesn't hit anything.
        Intersection empty = Intersection();
        if (i == empty)
        {
            break;
        }

        // Calculate additional information about the intersection.
        auto ctx = i.prepareComputations(ray);

        // Create a BSDF for the intersected material, which describes how it scatters light.
        auto m = ctx.matPtr;
        auto bsdf = m->createBSDF(ctx);

        // Accumulate the direct lighting at the intersection point.
        L += throughput * directLighting(ctx);
        
        // If the material is light-emitting, accumulate its emitted light.
        LightEmitting* leMaterial = dynamic_cast<LightEmitting*>(m.get()); 
        if (leMaterial) 
        {
            L += throughput * leMaterial->albedo().toVec3();
        }

        /// @brief Volume integration
        /// Modified from :
        /// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.
        // Calculates the interaction of a ray with the homogeneous volume, including its scattering and extinction effects.

        // Sample a new direction for the next ray bounce using the material's BSDF.
        float pdf;
        ngl::Vec3 Ls;
        ngl::Vec4 sampleDirection;
        bsdf->generateSample(ctx, sampleDirection, Ls, pdf);

        // Update the throughput based on the sampled direction.
        throughput = throughput * (Ls / pdf);

        // Create the next ray starting from the intersection point and moving in the sampled direction.
        Ray nextRay(ctx.point, sampleDirection);

        // Check if the material has volume properties (like smoke, fog).
        std::shared_ptr<Volume> volume = nullptr;
        if (m->hasVolume()) 
        {
            // Check if we're entering or exiting the volume.
            auto EyedotN = ctx.eye.dot(ctx.normal);
            auto dirDotN = sampleDirection.dot(ctx.normal.toVec3());
            auto transmit = (EyedotN < 0.0) != (dirDotN < 0.0);
            if (transmit) 
            {
                bool entered = dirDotN < 0.0f;
                if (entered) 
                {
                    nextRay.enterMaterial(m);
                } 
                else 
                {
                    nextRay.exitMaterial(m);
                }
            }
            
            volume = nextRay.getVolume(ctx);
        }
        
        // If we're inside a volume, integrate its effect.
        if (volume) 
        {
            ngl::Vec3 Lv;
            ngl::Vec3 transmittance;
            ngl::Vec3 weight;
            if (!volume->integrate(nextRay, Lv, transmittance, weight, ctx.point, nextRay, *ctx.object, m_rs, *this)) break;
            
            L += weight * throughput * Lv;
            throughput = throughput * transmittance;
        } 
        else 
        {
            // If not in a volume, check the next intersection.
            auto intersections = this->intersectScene(nextRay);
            auto xs = Intersection::intersections(intersections);
            auto i = Intersection::hit(xs);

            if (i == empty)
            {
                break;
            }
        }
        
        ray = nextRay;

        // end of citation
    }

    // Return the accumulated light/color.
    return L;
}