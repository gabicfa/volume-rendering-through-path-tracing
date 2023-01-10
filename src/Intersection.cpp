#include "Intersection.h"

Intersection::Intersection(float _t, int _object)
{
    m_t = _t;
    m_object = _object;
}

float Intersection::t() const
{
    return m_t;
}


int Intersection::object() const
{
    return m_object;
}

std::vector<Intersection> Intersection::intersections(const Intersection& _i1, const Intersection& _i2)
{
    std::vector<Intersection> intersections  = { _i1, _i2 };
    return intersections;
}
