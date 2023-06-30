#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include <ngl/Vec4.h>
#include <ngl/Mat4.h>

#include "OldMaterial.h"
#include "AbsMaterial.h"
class Intersection;
class Ray;

class Shape : public std::enable_shared_from_this<Shape>
{
    public:
        virtual ~Shape() = default;
        Shape();
        int id() const;
        void id(const int _id);
        ngl::Mat4 transform() const;
        void setTransform(const ngl::Mat4& _tMatrix);
        OldMaterial oldMaterial() const;
        void setOldMaterial(const OldMaterial& _m);

        std::shared_ptr<AbsMaterial> material() const;
        void setMaterial(const std::shared_ptr<AbsMaterial>& _m);

        virtual bool operator==(const Shape& _other) const = 0;
        virtual bool operator!=(const Shape& _other) const = 0;

        std::vector<Intersection> intersect(Ray _r);
        ngl::Vec4 normalAt(ngl::Vec4 _worldPoint);
        virtual ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) = 0;
        virtual std::vector<Intersection> localIntersect(Ray _r) = 0;

        std::shared_ptr<Shape> parent() const;
        void setParent(std::shared_ptr<Shape> shape);

        ngl::Vec4 worldToObject(const ngl::Vec4& _point) const;
        ngl::Vec4 normalToWorld(const ngl::Vec4& _normal) const;

    private:
        int m_id = 0;
        std::weak_ptr<Shape> m_parent;
        ngl::Mat4 m_transform = ngl::Mat4();
        OldMaterial m_material;
        std::shared_ptr<AbsMaterial> m_matPtr;

};

#endif
