#ifndef GROUP_H_
#define GROUP_H_

#include <vector>
#include <ngl/Mat4.h>
class Shape;
#include "Shape.h"
#include "Ray.h"

class Intersection;
#include "Intersection.h"

class Group : public Shape
{
    public:
        Group();
        int id() const override;
        bool operator==(const Shape& other) const override;
        bool operator!=(const Shape& other) const override;
        ngl::Mat4 transform() const override;
        void setTransform(const ngl::Mat4& _tMatrix) override;
        ngl::Vec4 normalAt(ngl::Vec4 _worldPoint) override;
        Material material() const override;
        void setMaterial(const Material& _m) override;
        std::vector<Intersection> intersect(Ray _r) override;
        void addChild(std::shared_ptr<Shape> shape);
        const std::vector<std::shared_ptr<Shape>>& getChildren() const;
    private:
        int m_id = 0;
        ngl::Mat4 m_transform = ngl::Mat4();
        Material m_material = Material();
        std::vector<Intersection> localIntersect(Ray _r);
        ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint);
        std::vector<std::shared_ptr<Shape>> m_children;
};

#endif
