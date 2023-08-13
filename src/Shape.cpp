#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"

Shape::Shape()
{
    m_id = 0;
}

int Shape::id() const 
{
    return m_id;
}

void Shape::id(const int _id)
{
    m_id = _id;
}

// Calculate intersections of a ray with the shape in the local coordinate system.
// Transforms the ray to local space before computing the intersections.
std::vector<Intersection> Shape::intersect(Ray _r)
{
    auto local_ray = _r.transform(transform().inverse());
    return localIntersect(local_ray);
}

// Get the parent shape. If the shape doesn't have a parent, it returns nullptr.
std::shared_ptr<Shape> Shape::parent() const
{
    return m_parent.lock();
}

// Set a new parent shape for this shape.
void Shape::setParent(std::shared_ptr<Shape> _parent)
{
    m_parent = _parent;
}

ngl::Mat4 Shape::transform() const
{
    return m_transform;
}

// Update the transformation matrix of the shape.
void Shape::setTransform(const ngl::Mat4& _tMatrix)
{
    m_transform =  m_transform * _tMatrix;
}

std::shared_ptr<Material> Shape::material() const
{
    return m_matPtr;
}

void Shape::setMaterial(const std::shared_ptr<Material>& _m)
{
    m_matPtr = _m;
}

// Convert a point in world space to object space.
// If the shape is part of a hierarchy, it applies all parent transformations recursively.
ngl::Vec4 Shape::worldToObject(const ngl::Vec4& _point) const
{
    ngl::Vec4 point = _point;
    if (auto parentShape = parent())
    {
        point = parentShape->worldToObject(point);
    }
    return transform().inverse() * point;
}

// Convert a normal in object space to world space.
// If the shape is part of a hierarchy, it applies all parent transformations recursively.
ngl::Vec4 Shape::normalToWorld(const ngl::Vec4& _normal) const
{
    ngl::Vec4 transformedNormal = transform().inverse().transpose() * _normal;
    transformedNormal.m_w = 0.0f;
    if (transformedNormal.length() > 0)
    {
        transformedNormal.normalize();
    }
    
    if (auto parentShape = parent())
    {
        transformedNormal = parentShape->normalToWorld(transformedNormal);
    }

    return transformedNormal;
}

// Calculate the normal at a given point on the shape in world coordinates.
ngl::Vec4 Shape::normalAt(ngl::Vec4 _worldPoint) 
{
    ngl::Vec4 localPoint = worldToObject(_worldPoint);
    ngl::Vec4 localNormal = localNormalAt(localPoint);
    ngl::Vec4 worldNormal = normalToWorld(localNormal);
    return worldNormal;
}

