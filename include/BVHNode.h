#ifndef BVH_H
#define BVH_H

#include "Shape.h"
#include "Group.h"
#include "AABB.h"

class BVHNode : public Shape {
    public:
        BVHNode();
        BVHNode(const Group& list, double time0, double time1);
        BVHNode(const std::vector<std::shared_ptr<Shape>>& src_objects, size_t start, size_t end, double time0, double time1);

        virtual std::vector<Intersection> localIntersect(Ray _r) override;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

        virtual bool operator==(const Shape& _other) const override;
        virtual bool operator!=(const Shape& _other) const override;
        virtual ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) override;

    public:
        std::shared_ptr<Shape> m_left;
        std::shared_ptr<Shape> m_right;
        AABB m_box;
};

#endif
