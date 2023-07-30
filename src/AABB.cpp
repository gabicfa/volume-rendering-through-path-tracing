#include "AABB.h"

bool AABB::intersect(const Ray& r, double t_min, double t_max) const {
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / r.direction()[a];
        auto t0 = (min()[a] - r.origin()[a]) * invD;
        auto t1 = (max()[a] - r.origin()[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}

AABB AABB::surroundingBox(const AABB& box0, const AABB& box1) {
    ngl::Vec3 small(
        std::min(box0.min().m_x, box1.min().m_x),
        std::min(box0.min().m_y, box1.min().m_y),
        std::min(box0.min().m_z, box1.min().m_z)
    );
    
    ngl::Vec3 big(
        std::max(box0.max().m_x, box1.max().m_x),
        std::max(box0.max().m_y, box1.max().m_y),
        std::max(box0.max().m_z, box1.max().m_z)
    );
    
    return AABB(small, big);
}

bool AABB::operator==(const AABB& other) const
{
    return minimum == other.minimum && maximum == other.maximum;
}

bool AABB::operator!=(const AABB& other) const
{
    return !(operator==(other));
}