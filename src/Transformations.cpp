#include "Transformations.h"

ngl::Mat4 Transformations::viewTransform(ngl::Vec4 from, ngl::Vec4 to, ngl::Vec4 down)
{
    auto forward = (to - from).normalize();
    auto left = forward.cross(down.normalize());
    auto trueDown = left.cross(forward);

    auto orientation = ngl::Mat4(left.m_x, left.m_y, left.m_z, 0,
                                 trueDown.m_x, trueDown.m_y, trueDown.m_z, 0,
                                 -forward.m_x, -forward.m_y, -forward.m_z, 0,
                                 0, 0, 0, 1);
    return orientation * ngl::Mat4::translate(-from.m_x, -from.m_y, -from.m_z);
    
}