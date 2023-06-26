#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"
#include "Material.h"

Shape::Shape()
{
    m_id = 0;
    m_material = Material();
}

int Shape::id() const 
{
    return m_id;
}

void Shape::id(const int _id)
{
    m_id = _id;
}

std::vector<Intersection> Shape::intersect(Ray _r)
{
    auto local_ray = _r.transform(transform().inverse());
    return localIntersect(local_ray);
}

std::shared_ptr<Shape> Shape::parent() const
{
    return m_parent.lock();
}

void Shape::setParent(std::shared_ptr<Shape> _parent)
{
    m_parent = _parent;
}

ngl::Mat4 Shape::transform() const
{
    return m_transform;
}

void Shape::setTransform(const ngl::Mat4& _tMatrix)
{
    m_transform =  m_transform * _tMatrix;
}

Material Shape::material() const
{
    return m_material;
}

void Shape::setMaterial(const Material& _m)
{
    m_material = _m;
}

ngl::Vec4 Shape::worldToObject(const ngl::Vec4& _point) const
{
    ngl::Vec4 point = _point;
    if (auto parentShape = parent())
    {
        point = parentShape->worldToObject(point);
    }
    return transform().inverse() * point;
}

ngl::Vec4 Shape::normalToWorld(const ngl::Vec4& _normal) const
{
    ngl::Vec4 transformedNormal = transform().inverse().transpose() * _normal;
    transformedNormal.m_w = 0.0f;
    transformedNormal.normalize();

    if (auto parentShape = parent())
    {
        transformedNormal = parentShape->normalToWorld(transformedNormal);
    }

    return transformedNormal;
}

ngl::Vec4 Shape::normalAt(ngl::Vec4 _worldPoint) 
{
    ngl::Vec4 localPoint = worldToObject(_worldPoint);
    ngl::Vec4 localNormal = localNormalAt(localPoint);
    ngl::Vec4 worldNormal = normalToWorld(localNormal);
    return worldNormal;
}
