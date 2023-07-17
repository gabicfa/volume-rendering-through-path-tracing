#ifndef GROUP_H_
#define GROUP_H_

#include <vector>
#include <ngl/Mat4.h>

#include "Shape.h"
#include "Ray.h"
#include "Intersection.h"

class Group : public Shape
{
    public:
        Group();
        bool operator==(const Shape& _other) const override;
        bool operator!=(const Shape& _other) const override;
        void addChild(std::shared_ptr<Shape> _shape);
        const std::vector<std::shared_ptr<Shape>>& getChildren() const;
        std::vector<Intersection> localIntersect(Ray _r) override;
        ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) override;
    private:
        std::vector<std::shared_ptr<Shape>> m_children;
};

#endif
