#include "Tuple.h"

Tuple::Tuple(float _x, float _y) : m_x(_x), m_y{_y}
{}

float Tuple::getX() const
{
    return m_x;
}

float Tuple::getY() const
{
    return m_y;
}