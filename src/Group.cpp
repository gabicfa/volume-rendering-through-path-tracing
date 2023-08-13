#include "Group.h"

Group::Group()
{
}

// Equality operator checks if two groups (or a group and another shape) are identical based on their IDs and transformations.
bool Group::operator==(const Shape& _other) const
{
    if (const Group* group = dynamic_cast<const Group*>(&_other))
    {
        return id() == group->id() && transform() == group->transform();
    }
    return false;
}

// Inequality operator leverages the equality operator to determine if two groups are different.
bool Group::operator!=(const Shape& _other) const
{
    return !(*this == _other);
}

// Finds intersections between the ray and all children shapes within the group.
/// @brief ray intersecting group
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
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
// end of citation

// Placeholder method since Groups do not have their own normals like primitive shapes.
// Typically, this method would not be invoked on a Group, and it's present due to inheritance.
ngl::Vec4 Group::localNormalAt(ngl::Vec4 _localPoint)
{
    return _localPoint;
}

// Adds a child shape to the group's list of children and sets the group as the shape's parent.
void Group::addChild(std::shared_ptr<Shape> _shape)
{
    _shape->setParent(shared_from_this());
    m_children.push_back(_shape);
}

// Getter method for retrieving all child shapes within the group.
const std::vector<std::shared_ptr<Shape>>& Group::getChildren() const
{ 
    return m_children; 
}