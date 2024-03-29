#include "Intersection.h"
#include "Computation.h"
#include "Shape.h"
#include "Sphere.h"

Intersection::Intersection()
{
    m_t = 0;
    m_object = nullptr;
}

Intersection::Intersection(float _t, std::shared_ptr<Shape> _object)
{
    m_t = _t;
    m_object = _object;
}

bool Intersection::operator==(const Intersection& _other) const
{
    return m_t == _other.m_t && m_object == _other.m_object;
}

bool Intersection::operator!=(const Intersection& _other) const
{
    return !(*this == _other);
}

float Intersection::t() const
{
    return m_t;
}

std::shared_ptr<Shape> Intersection::object() const
{
    return m_object;
}

std::vector<Intersection> Intersection::intersections(std::vector<Intersection> _intersections)
{
    // Sort the intersections based on their t-values in ascending order.
    std::sort(_intersections.begin(), _intersections.end(), [](const Intersection &a, const Intersection &b) 
    {
        return a.t() < b.t();
    });
    return _intersections;
}

Intersection Intersection::hit(std::vector<Intersection> _intersections)
{
    // Find the first intersection with a positive t-value (considering a small threshold).
    auto it = std::find_if(_intersections.begin(), _intersections.end(), [](const Intersection& i) {
        return i.t() >= 0.001;
    });

    if (it != _intersections.end())
    {
        return *it;
    }
    
    return Intersection();
}

Intersection Intersection::nextHitAfter(const Intersection& currentHit, const std::vector<Intersection>& sortedIntersections) {
    // Find the intersection following the current one in the sorted list.
    auto it = std::find(sortedIntersections.begin(), sortedIntersections.end(), currentHit);

    if (it != sortedIntersections.end()) {
        ++it;

        if (it != sortedIntersections.end()) {
            return *it;
        }
    }

    return Intersection();
}

Computation Intersection::prepareComputations(Ray _r)
{
    // Prepare computations at the intersection point, calculating necessary values like point, eye vector, and normal.
    Computation comp;
    comp.t = this->m_t;
    comp.object = m_object;
    comp.point = _r.position(comp.t);
    comp.eye = -(_r.direction());
    comp.incomingRay = _r;
    comp.normal = comp.object->normalAt(comp.point);
    comp.matPtr = m_object->material();

    // Adjust the normal vector based on the direction of the incoming ray.
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