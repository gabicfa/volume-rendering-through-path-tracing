#include "Intersection.h"
#include "Sphere.h"

Intersection::Intersection()
{
    m_t = 0;
    m_object = std::make_shared<Sphere>();
}

Intersection::Intersection(float _t, std::shared_ptr<Sphere> _object)
{
    m_t = _t;
    m_object = _object;
}

bool Intersection::operator==(const Intersection& other) const
{
    return m_t == other.m_t && *m_object == *(other.m_object);
}

bool Intersection::operator!=(const Intersection& other) const
{
    return !(*this == other);
}


float Intersection::t() const
{
    return m_t;
}

std::shared_ptr<Sphere> Intersection::object() const
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
    auto it = std::find_if(intersections.begin(), intersections.end(), [](const Intersection& i) {
        return i.t() >= 0;
    });

    if (it != intersections.end())
    {
        return *it;
    }
    
    return Intersection();
}

Computation Intersection::prepareComputations(Ray _r)
{
    Computation comp;
    comp.t = this->m_t;
    comp.object = std::make_shared<Sphere>(*m_object); // Assign a new shared_ptr
    comp.point = _r.position(comp.t);
    comp.eye = -(_r.direction());
    comp.normal = comp.object->normalAt(comp.point);

    if (comp.normal.dot(comp.eye) < 0)
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
