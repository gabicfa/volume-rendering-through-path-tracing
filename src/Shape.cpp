#include "Shape.h"
#include "Group.h"

std::shared_ptr<Shape> Shape::parent() const
{
    return m_parent.lock();
}

void Shape::setParent(std::shared_ptr<Shape> parent)
{
    m_parent = parent;
}