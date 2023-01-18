#include "Intersection.h"
#include "Sphere.h"

Intersection::Intersection()
{
    m_t = 0;
    m_object = new Sphere();
}

Intersection::Intersection(float _t, Sphere *_object)
{
    m_t = _t;
    m_object = _object;
}

bool Intersection::operator==(const Intersection& other) const 
{
    return m_t == other.t() && *m_object == other.object();
}

bool Intersection::operator!=(const Intersection& other) const 
{
    return m_t != other.t() || *m_object != other.object();
}

float Intersection::t() const
{
    return m_t;
}

Sphere& Intersection::object() const
{
    return *m_object;
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

Computation Intersection::prepareComputations(Ray _r)
{
    Computation comp;
    comp.t = this->m_t;
    comp.object = this->m_object;
    comp.point = _r.position(comp.t);
    comp.eye = -(_r.direction());
    comp.normal = comp.object->normalAt(comp.point);

    if(comp.normal.dot(comp.eye) < 0)
    {
        comp.inside = true;
        comp.normal = -comp.normal;
    }
    else 
    {
        comp.inside = false;
    }
    return comp;
}
