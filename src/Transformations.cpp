#include "Transformations.h"

ngl::Mat4 Transformations::viewTransform(ngl::Vec4 from, ngl::Vec4 to, ngl::Vec4 up)
{
    auto forward = (to - from).normalize();
    auto upn = up.normalize();
    auto right = upn.cross(forward);
    auto trueUp = forward.cross(right);

    auto orientation = ngl::Mat4(right.m_x, right.m_y, -right.m_z, 0,
                                 trueUp.m_x, trueUp.m_y, -trueUp.m_z, 0,
                                 -forward.m_x, -forward.m_y, forward.m_z, 0,
                                 0, 0, 0, 1);
    return orientation * ngl::Mat4::translate(-from.m_x, -from.m_y, -from.m_z);  
}