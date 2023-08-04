#include "Scene.h"
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include "Triangle.h"
#include "ObjFile.h"
#include "Sphere.h"
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
    auto materialWhite = std::make_shared<Lambertian>(ngl::Vec4(0.5, 0.5, 0.5 ));

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

void openPyramid (Scene &scene, std::shared_ptr<Material> material)
{
    ObjFile pyramid("files/Pyramid.obj");
    auto pyramidGroup = pyramid.defaultGroup();
    for (auto t=0; t < pyramidGroup->getChildren().size(); t ++)
    {
        auto triangle = std::dynamic_pointer_cast<Triangle>(pyramidGroup->getChildren()[t]);
        triangle->setMaterial(material);
        triangle->setTransform(ngl::Mat4::translate(-0.71, -0.6, -1.0));
        triangle->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
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
    auto materialBeers = std::make_shared<BeersLawMaterial>(ngl::Vec3(0.2, 0.2, 0.2));
    auto materialSingleScatterHomo = std::make_shared<SingleScatterHomogeneousMaterial>(ngl::Vec3(0.0, 0.0, 1.0), ngl::Vec3(0.1, 0.1, 0.1));
    auto materialHete = std::make_shared<BeersLawHeterogeneousMaterial>(0.9, 1);
    auto materialDielectric = std::make_shared<Dielectric>(-0.4);
    auto difflight = std::make_shared<LightEmitting>(ngl::Vec3(4,4,4));
    auto difflight2 = std::make_shared<LightEmitting>(ngl::Vec3(5,5,5));

    auto materialGreen = std::make_shared<Lambertian>(ngl::Vec4(0.0, 1.0, 0.0));
    auto materialRed = std::make_shared<Lambertian>(ngl::Vec4(1.0, 0.0, 0.0));
    auto materialWhite = std::make_shared<Lambertian>(ngl::Vec4(0.5, 0.5, 0.5 ));
    auto materialGray = std::make_shared<Lambertian>(ngl::Vec4(0.45, 0.45, 0.45));

    auto materialCenter = std::make_shared<Lambertian>(ngl::Vec4(0.7, 0.3, 0.3));
    auto materialLeft   = std::make_shared<Metal>(ngl::Vec4(0.8, 0.8, 0.8));
    auto materialRight  = std::make_shared<Metal>(ngl::Vec4(0.8, 0.6, 0.2));

    if (mode == SceneMode::Scene1)
    {
        openCornelBox(*this);
    }
    else if (mode == SceneMode::Scene2)
    {
        openPyramid(*this, materialLeft);
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

        // auto s2 = std::make_shared<Sphere>(2, materialBack);
        // s2->setTransform(ngl::Mat4::translate(0.0, -1.0, -95.5));
        // s2->setTransform(ngl::Mat4::scale(100.0f, 100.0f, 100.0f));
        // this->addObject(s2);

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
        auto sphere = std::make_shared<Sphere>(1, materialGray);
        this->addObject(sphere);
    }
}

Scene::Scene(bool _default, int num)
{
        

        
}

std::vector<std::shared_ptr<Shape>>& Scene::objects()
{
    return m_objects;
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
        if (c.matPtr && c.matPtr->scatter(_r, c, attenuation, scattered))
            return attenuation * colorAt(scattered, depth-1);
        return ngl::Vec3(0.0f,0.0f,0.0f);
        // return shadeHit(c);
    }
}

//method to compute beam transmittance
ngl::Vec3 Scene::transmittance() const {
    return ngl::Vec3(1.f, 1.f, 1.f);
}

void Scene::generateLightSample(const Computation &ctx, ngl::Vec4 &sampleDirection, ngl::Vec3 &L,
                         float &pdf, ngl::Vec3 &beamTransmittance) {

    L = m_light.sampleLi(ctx, &sampleDirection, &pdf);

    if (pdf > 0 && !isBlack(L)) {
        beamTransmittance = this->transmittance();
    } else {
        beamTransmittance = ngl::Vec3(0.f, 0.f, 0.f);
    }
}

// struct RectAreaLight {
//     ngl::Vec3 center;  // Position of the light's center
//     float width, height;  // Dimensions of the light
//     ngl::Vec3 color;  // Radiance (color) of the light
//     ngl::Vec3 u, v;  // Two orthogonal vectors defining the light's orientation
// };

// void Scene::generateLightSample(const Computation &ctx, ngl::Vec4 &sampleDirection, ngl::Vec3 &L,
//                          float &pdf, ngl::Vec3 &beamTransmittance) {
//     // For simplicity, assume we only have one rectangular area light in the scene
//     ngl::Vec4 center (0.0f, 0.9f, -.8f);
//     float width = 1.0f;
//     float height = 1.0f; 
//     ngl::Vec3 color (1.0f,1.0f,1.0f); // Radiance (color) of the light
//     ngl::Vec4 u (1.0f,0.0f,0.0f);
//     ngl::Vec4 v (0.0f,0.0f,-1.0f);

//     // Sample a random point within the light's area
//     float randomX = randomDouble(-0.5, 0.5); // Gives a value between -0.5 and 0.5
//     float randomY = randomDouble(-0.5, 0.5); // Gives a value between -0.5 and 0.5

//     ngl::Vec4 randomPosition = center + randomX * width * u + randomY * height * v;
    
//     // Compute direction from the point to the sampled position on the light
//     auto sampleDirectionNotNormalized = (randomPosition - ctx.point);
//     sampleDirectionNotNormalized.normalize();
//     sampleDirection = sampleDirectionNotNormalized;
//     // The radiance is simply the light's color
//     L = color;

//     // The pdf is 1 over the area of the light
//     float area = width * height;
//     pdf = 1.0f / area;

//     // For simplicity, assuming that the beam transmittance is 1 (no light is blocked or absorbed)
//     // In reality, you would calculate the actual beam transmittance based on objects in the scene and their material properties
//     beamTransmittance = ngl::Vec3(1.0, 1.0, 1.0);
// }


void Scene::evaluateLightSample(const Computation &ctx, const ngl::Vec4 &sampleDirection,
                         ngl::Vec3 &L, float &pdf, ngl::Vec3 &beamTransmittance) {
    // evaluate radiance and pdf using scene's light source
    L = m_light.le(Ray(ctx.point, sampleDirection));
    pdf = m_light.pdfLi();

    if (pdf > 0 && !isBlack(L)) {
        // calculate the beam transmittance
        beamTransmittance = this->transmittance();
    } else {
        beamTransmittance = ngl::Vec3(0.f, 0.f, 0.f);
    }
}

void Scene::evaluateLightSample(const Computation &ctx, const ngl::Vec4 &sampleDirection,
                         ngl::Vec3 &L, float &pdf) {
    L = m_light.le(Ray(ctx.point, sampleDirection));
    pdf = m_light.pdfLi();
}

float Scene::MISWeight(int nsamps1, float pdf1, int nsamps2, float pdf2)
{
    // calculate the weight for the first sampling technique
    float weight1 = nsamps1 * pdf1;
    // calculate the weight for the second sampling technique
    float weight2 = nsamps2 * pdf2;

    // return the balance heuristic weight
    return weight1 / (weight1 + weight2);
}

ngl::Vec3 Scene::directLighting(const Computation& comp)
{
    ngl::Vec3 Li(0, 0, 0);
    ngl::Vec3 L(0, 0, 0);
    auto N = comp.normal;
    auto P = comp.point;
    ngl::Vec4 wi;
    float pdf;
    ngl::Vec3 beamTransmittance;

    generateLightSample(comp, wi, Li, pdf, beamTransmittance);

    float lightDistance = (m_light.position() - P).length();

    // Ray shadowRay(P, wi);
    // auto shadowIntersections = intersectScene(shadowRay);
    // auto xs = Intersection::intersections(shadowIntersections);
    // auto i = Intersection::hit(xs);

    // if(i != Intersection() && i.t() > 0.0001f && i.t() < lightDistance)
    // {
    //     return ngl::Vec3(0.0f, 0.0f, 0.0f); 
    // }

    if(pdf > 0.f && !isBlack(Li))
    {
        float cosTheta = std::max(0.0f, N.dot(ngl::Vec3(wi.m_x, wi.m_y, wi.m_z)));
        if (cosTheta > 0)
        {
            L += comp.matPtr->albedo().toVec3() * Li * cosTheta * beamTransmittance / pdf;
        }
    }

    return L;
}

bool Scene::isOccluded(const ngl::Vec4 &point, const ngl::Vec4 &direction) {
    // Create a ray starting from the point and going in the direction
    Ray ray(point, direction);
    
    // Initialize the nearest intersection to be at infinity
    float nearestT = std::numeric_limits<float>::infinity();
    Intersection nearestIntersection;

    // Check for intersection with each object in the scene
    for (auto& object : m_objects) {
        auto intersections = intersectScene(ray);
        auto xs = Intersection::intersections(intersections);
        auto i = Intersection::hit(xs);
        if(i != Intersection() && i.t() > 0.001f && i.t() < nearestT) {
            // Ignore intersections at the starting point (t == 0)
            nearestT = i.t();
            nearestIntersection = i;
        }
    }

    // If the nearest intersection is at infinity, there is no occlusion
    return nearestT != std::numeric_limits<float>::infinity();
}

// ngl::Vec3 Scene::directLighting(const Computation& comp)
// {
//     ngl::Vec3 L = ngl::Vec3(0.0, 0.0, 0.0);  // Initialize radiance to black

//     // Iterate over each light source in the scene
//     ngl::Vec4 sampleDirection;
//     ngl::Vec3 sampleRadiance, beamTransmittance;
//     float pdf;

//     // Sample the light source
//     generateLightSample(comp, sampleDirection, sampleRadiance, pdf, beamTransmittance);

//     // Check if the light source is visible from the point
//     if (!isOccluded(comp.point, sampleDirection)) {
//         float cosTheta = std::max(0.0f, comp.normal.dot(sampleDirection));

//         // Accumulate the radiance contribution from this light
//         L += (sampleRadiance * cosTheta * beamTransmittance) / pdf;
//     }


//     return L;
// }

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

        // if(dynamic_cast<LightEmitting*>(m.get())) {
        //     L += throughput * m->albedo().toVec3();
        // }

        // Sample direction for next ray from BSDF
        float pdf;
        ngl::Vec3 Ls;
        ngl::Vec4 sampleDirection;
        bsdf->generateSample(ctx, sampleDirection, Ls, pdf);

        throughput = throughput * (Ls / pdf);
        // throughput = throughput * m->albedo().toVec3() * (Ls / pdf);

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
            if (!volume->integrate(nextRay, Lv, transmittance, weight, ctx.point, nextRay, *ctx.object, *this)) break;
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