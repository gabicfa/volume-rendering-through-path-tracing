#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
#include <vector>
#include "Shape.h"
#include "AreaLight.h"
#include "RendererServices.h"
#include "Light.h"
#include "Computation.h"
#include <ngl/Vec3.h>

// The Scene class defines the environment that contains all the 3D objects, lights, and 
// related properties. It facilitates scene creation, lighting computation, and interactions 
// between rays and objects.
class Scene
{
    public:
        // Predefined scene configurations.
        enum class SceneMode
        {
            Default,
            Scene1,
            Scene2,
            Scene3,
            Scene4,
            Scene5,
            Scene6,
            Scene7
        };

        Scene(bool _default = false);

        // Sets the scene based on predefined configurations.
        void chooseScene (SceneMode mode);

        // Accessors and modifiers for scene properties.
        std::vector<std::shared_ptr<Shape>>& objects();
        AreaLight areaLight() const;
        void areaLight(AreaLight _l);
        RendererServices rs() const;
        void rs(RendererServices _rs);
        Light light() const;
        void light(Light _l);

        // Lighting and shading computations.
        ngl::Vec3 directLighting(const Computation& comp);
        float softShadowFactor(const Computation &comp, int numSamples); 

        // Scene operations.
        void addObject(std::shared_ptr<Shape> s);
        std::vector<Intersection> intersectScene(Ray _r);
        ngl::Vec3 pathTrace(const Ray& r, int maxDepth);

    private:
        // Collection of all 3D objects present in the scene.
        std::vector<std::shared_ptr<Shape>> m_objects;
        
        // Area light source used for scene illumination.
        AreaLight m_areaLight;
        
        // Point light source in the scene.
        Light m_light;
        
        // Renderer services to sample light
        RendererServices m_rs;
};

#endif