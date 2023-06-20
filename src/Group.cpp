#include "Group.h"

Group::Group()
{
}

bool Group::operator==(const Shape& other) const
{
    if (const Group* group = dynamic_cast<const Group*>(&other))
    {
        return id() == group->id() && transform() == group->transform();
    }
    return false;
}

bool Group::operator!=(const Shape& other) const
{
    return !(*this == other);
}

std::vector<Intersection> Group::intersect(Ray _r)
{
    auto local_ray = _r.transform(transform().inverse());
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
