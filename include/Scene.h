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

class Scene
{
    public:
        enum class SceneMode
        {
            Default,
            Scene1,
            Scene2,
            Scene3,
            Scene4,
            Scene5
        };

        static SceneMode intToSceneMode(int index) {
            switch (index) {
                case 0: return SceneMode::Default;
                case 1: return SceneMode::Scene1;
                case 2: return SceneMode::Scene2;
                case 3: return SceneMode::Scene3;
                case 4: return SceneMode::Scene4;
                case 5: return SceneMode::Scene5;
                default:
                    std::cerr << "Invalid scene index: " << index << std::endl;
                    return SceneMode::Default; // default case if index is out of bounds
            }
        }
        Scene(bool _default = false);
        void chooseScene (SceneMode mode);
        std::vector<std::shared_ptr<Shape>>& objects();
        AreaLight areaLight() const;
        void areaLight(AreaLight _l);
        RendererServices rs() const;
        void rs(RendererServices _rs);
        Light light() const;
        void light(Light _l);
        ngl::Vec3 directLighting(const Computation& comp);
        void addObject(std::shared_ptr<Shape> s);
        std::vector<Intersection> intersectScene(Ray _r);
        ngl::Vec3 pathTrace(const Ray& r, int maxDepth);
        float softShadowFactor(const Computation &comp, int numSamples); 
        std::pair<bool, ngl::Vec3> computeTransmittance(const ngl::Vec4 &start, const ngl::Vec4 &end);

    private:
        std::vector<std::shared_ptr<Shape>> m_objects;
        AreaLight m_areaLight;
        Light m_light;
        RendererServices m_rs;
};
#endif