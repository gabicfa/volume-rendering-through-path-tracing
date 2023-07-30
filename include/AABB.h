#ifndef AABB_H
#define AABB_H

#include "Ray.h"
#include <ngl/Vec3.h>

class AABB {
    public:
        AABB() {}
        AABB(const ngl::Vec3& a, const ngl::Vec3& b) : minimum(a), maximum(b) {}

        ngl::Vec3 min() const { return minimum; }
        ngl::Vec3 max() const { return maximum; }

        bool intersect(const Ray& r, double t_min, double t_max) const;
        static AABB surroundingBox(const AABB& box0, const AABB& box1);

        bool operator==(const AABB& other) const;
        bool operator!=(const AABB& other) const;

    private:
        ngl::Vec3 minimum;
        ngl::Vec3 maximum;
};

#endif
