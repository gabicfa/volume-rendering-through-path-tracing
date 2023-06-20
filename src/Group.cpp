#include "Group.h"

Group::Group()
{
}

bool Group::operator==(const Shape& other) const
{
    return true;
}

bool Group::operator!=(const Shape& other) const
{
    return false;
}

std::vector<Intersection> Group::intersect(Ray _r)
{
    auto local_ray = _r.transform(m_transform.inverse());
    return localIntersect(local_ray);
}

std::vector<Intersection> Group::localIntersect(Ray _r)
{
    std::vector<Intersection> intersections;

    // Iterate over each child shape and collect their intersections with the ray
    for (const auto& shape : m_children)
    {
        auto childIntersections = shape->intersect(_r);
        intersections.insert(intersections.end(), childIntersections.begin(), childIntersections.end());
    }

    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) 
    {
        return a.t() < b.t();
    });
    return intersections;

    return intersections;
}

ngl::Mat4 Group::transform() const
{
    return m_transform;
}

void Group::setTransform(const ngl::Mat4& _tMatrix)
{
    auto newTransform = _tMatrix * m_transform;
    m_transform = newTransform;
}

int Group::id() const
{
    return m_id;
}

Material Group::material() const
{
    return m_material;
}

void Group::setMaterial(const Material& _m)
{
    m_material = _m;
}

ngl::Vec4 Group::normalAt(ngl::Vec4 _worldPoint)
{
    auto objPoint = m_transform.inverse() * _worldPoint;
    auto objNormal = localNormalAt(objPoint);
    auto worldNormal = (m_transform.inverse()).transpose() * objNormal;
    worldNormal.m_w = 0.0f;
    return worldNormal.normalize();
}

ngl::Vec4 Group::localNormalAt(ngl::Vec4 _localPoint)
{
    return _localPoint;
}

void Group::addChild(std::shared_ptr<Shape> shape)
{
    shape->setParent(shared_from_this());
    m_children.push_back(shape);
}

const std::vector<std::shared_ptr<Shape>>& Group::getChildren() const
{ 
    return m_children; 
}
