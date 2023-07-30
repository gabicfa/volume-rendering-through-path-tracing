#include "Group.h"
#include "Utility.h"
Group::Group()
{
}

bool Group::operator==(const Shape& _other) const
{
    if (const Group* group = dynamic_cast<const Group*>(&_other))
    {
        return id() == group->id() && transform() == group->transform();
    }
    return false;
}

bool Group::operator!=(const Shape& _other) const
{
    return !(*this == _other);
}

std::vector<Intersection> Group::localIntersect(Ray _r)
{
    std::vector<Intersection> intersections;

    for (const auto& _shape : m_children)
    {
        auto childIntersections = _shape->intersect(_r);
        intersections.insert(intersections.end(), childIntersections.begin(), childIntersections.end());
    }

    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) 
    {
        return a.t() < b.t();
    });
    return intersections;
}

ngl::Vec4 Group::localNormalAt(ngl::Vec4 _localPoint)
{
    return _localPoint;
}

void Group::addChild(std::shared_ptr<Shape> _shape)
{
    _shape->setParent(shared_from_this());
    m_children.push_back(_shape);
}

const std::vector<std::shared_ptr<Shape>>& Group::getChildren() const
{ 
    return m_children; 
}

bool Group::boundingBox(double time0, double time1, AABB& outputBox) const
{
    if (m_children.empty())
        return false;

    AABB tempBox;
    bool firstBox = true;

    for (const auto& shape : m_children)
    {
        if (!shape->boundingBox(time0, time1, tempBox))
            return false;

        outputBox = firstBox ? tempBox : AABB::surroundingBox(outputBox, tempBox);
        firstBox = false;
    }
    
    return true;
}