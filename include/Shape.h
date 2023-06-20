#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include <ngl/Vec4.h>
#include "Material.h"
#include "Ray.h"

class Intersection;
#include "Intersection.h"

class Shape : public std::enable_shared_from_this<Shape>
{
    public:
        virtual ~Shape() = default;
        virtual int id() const = 0;
        ngl::Mat4 transform() const;
        void setTransform(const ngl::Mat4& _tMatrix);
        Material material() const;
        void setMaterial(const Material& _m);

        virtual bool operator==(const Shape& other) const = 0;
        virtual bool operator!=(const Shape& other) const = 0;

        virtual std::vector<Intersection> intersect(Ray _r) = 0;
        ngl::Vec4 normalAt(ngl::Vec4 _worldPoint);
        virtual ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) = 0;

        std::shared_ptr<Shape> parent() const;
        void setParent(std::shared_ptr<Shape> shape);

        ngl::Vec4 worldToObject(const ngl::Vec4& point) const;
        ngl::Vec4 normalToWorld(const ngl::Vec4& normal) const;

    private:
        std::weak_ptr<Shape> m_parent;
        ngl::Mat4 m_transform = ngl::Mat4();
        Material m_material = Material();

};

#endif
