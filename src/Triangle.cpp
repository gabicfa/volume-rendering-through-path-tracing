#include "Triangle.h"
#include "Ray.h"
#include "Intersection.h"

auto EPSILON = 0.001f;

// Constructor computes edges and normal based on the provided vertices.
Triangle::Triangle(const ngl::Vec4& p1, const ngl::Vec4& p2, const ngl::Vec4& p3)
    : m_p1(p1), m_p2(p2), m_p3(p3)
{
    m_e1 = m_p2 - m_p1;
    m_e2 = m_p3 - m_p1;
    auto _n =  m_e2.cross(m_e1);
    m_normal = _n;
    if (_n.length() > 0)
    {
         m_normal =_n.normalize();
    }
   
}

// Constructor computes edges, normal and sets material based on provided vertices and material.
Triangle::Triangle(const ngl::Vec4& p1, const ngl::Vec4& p2, const ngl::Vec4& p3,  std::shared_ptr<Material> _matPtr)
    : m_p1(p1), m_p2(p2), m_p3(p3)
{
    m_e1 = m_p2 - m_p1;
    m_e2 = m_p3 - m_p1;
    auto _n =  m_e2.cross(m_e1);
    m_normal = _n;
    if (_n.length() > 0)
    {
         m_normal =_n.normalize();
    }
    this->setMaterial(_matPtr);
}

const ngl::Vec4& Triangle::getP1() const
{
    return m_p1;
}

const ngl::Vec4& Triangle::getP2() const
{
    return m_p2;
}

const ngl::Vec4& Triangle::getP3() const
{
    return m_p3;
}

const ngl::Vec4& Triangle::getE1() const
{
    return m_e1;
}

const ngl::Vec4& Triangle::getE2() const
{
    return m_e2;
}

const ngl::Vec4& Triangle::getNormal() const
{
    return m_normal;
}

// Equality comparison based on triangle vertices.
bool Triangle::operator==(const Shape& other) const
{
    if (const Triangle* triangle = dynamic_cast<const Triangle*>(&other))
    {
        return (m_p1 == triangle->m_p1) &&
               (m_p2 == triangle->m_p2) &&
               (m_p3 == triangle->m_p3);
    }
    return false;
}

bool Triangle::operator!=(const Shape& other) const
{
    return !(*this == other);
}

// Returns the triangle's normal.
ngl::Vec4 Triangle::localNormalAt(ngl::Vec4 _localPoint)
{
    return m_normal;
}

// Computes the intersection point between a ray and the triangle using the Moller-Trumbore intersection algorithm.

/// @brief ray intersecting triangle
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
std::vector<Intersection> Triangle::localIntersect(Ray _r)
{
    // Implementation of Moller-Trumbore intersection algorithm.
    ngl::Vec4 dirCrossE2 = _r.direction().cross(m_e2);
    float det = m_e1.dot(dirCrossE2);

    if (std::abs(det) < EPSILON)
    {
        return std::vector<Intersection>();
    }
    else
    {
        float f = 1.0f / det;

        ngl::Vec4 p1ToOrigin = _r.origin() - m_p1;
        float u = f * p1ToOrigin.dot(dirCrossE2);

        if (u < 0 || u > 1)
        {
            return std::vector<Intersection>();
        }

        ngl::Vec4 originCrossE1 = p1ToOrigin.cross(m_e1);
        float v = f * _r.direction().dot(originCrossE1);

        if (v < 0 || (u + v) > 1)
        {
            return std::vector<Intersection>();
        }

        float t = f * m_e2.dot(originCrossE1);

        Intersection intersection(t, std::make_shared<Triangle>(*this));
        return std::vector<Intersection>{intersection};
    }
}
// end citation