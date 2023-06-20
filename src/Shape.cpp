#include "Shape.h"

std::shared_ptr<Shape> Shape::parent() const
{
    return m_parent.lock();
}

void Shape::setParent(std::shared_ptr<Shape> parent)
{
    m_parent = parent;
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

ngl::Vec4 Shape::normalToWorld(const ngl::Vec4& normal) const
{
    ngl::Vec4 transformedNormal = transform().inverse().transpose() * normal;
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
    ngl::Vec4 local_point = worldToObject(_worldPoint);
    ngl::Vec4 local_normal = localNormalAt(local_point);
    ngl::Vec4 world_normal = normalToWorld(local_normal);
    return world_normal;
}
