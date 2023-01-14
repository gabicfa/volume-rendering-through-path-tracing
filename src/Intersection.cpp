#include "Intersection.h"

Intersection::Intersection(float _t, int _object)
{
    m_t = _t;
    m_object = _object;
}

bool Intersection::operator==(const Intersection& other) const 
{
    return m_t == other.t() && m_object == other.object();
}

bool Intersection::operator!=(const Intersection& other) const 
{
    return m_t != other.t() || m_object != other.object();
}

float Intersection::t() const
{
    return m_t;
}


int Intersection::object() const
{
    return m_object;
}

std::vector<Intersection> Intersection::intersections(std::vector<Intersection> intersections )
{
    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) 
    {
        return a.t() < b.t();
    });
    return intersections;
}

Intersection Intersection::hit(std::vector<Intersection> intersections)
{
    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) 
    {
        return a.t() < b.t();
    });
    for(Intersection i : intersections)
    {
        if (i.t() >= 0) return i;
    }
    return Intersection();
}
