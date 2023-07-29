#ifndef RAY_H_
#define RAY_H_

#include <ngl/Vec4.h>
#include <ngl/Mat4.h>
#include <vector>
#include <memory>

class Material;
class Computation;
class Volume;

class Ray
{
public:
    Ray();
    Ray(ngl::Vec4 _origin, ngl::Vec4 _direction);
    Ray(const Ray &ray);
    ngl::Vec4 origin() const;
    ngl::Vec4 direction() const;
    ngl::Vec4 position(float _t);
    Ray transform(ngl::Mat4 _tMatrix);
    void enterMaterial(std::shared_ptr<Material> b);
    void exitMaterial(std::shared_ptr<Material> b);
    std::shared_ptr<Volume> getVolume(Computation &_comp) const;

private:
    ngl::Vec4 m_origin;
    ngl::Vec4 m_direction;
    std::vector<std::shared_ptr<Material>> m_volumes;
};

#endif
