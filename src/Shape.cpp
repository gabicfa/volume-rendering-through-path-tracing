#include "Shape.h"

std::shared_ptr<Shape> Shape::parent() const
{
    return m_parent.lock();
}

void Shape::setParent(std::shared_ptr<Shape> parent)
{
    m_parent = parent;
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