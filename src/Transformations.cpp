#include "Transformations.h"

/// @brief builds camera transformation matrix
/// Modified from :
/// Jamis Buck (2019). The Ray Tracer Challenge The Pragmatic Bookshelf. Raleigh, North Carolina:The Pragmatic Bookshelf 
ngl::Mat4 Transformations::viewTransform(ngl::Vec4 from, ngl::Vec4 to, ngl::Vec4 up)
{
    auto forward = (to - from).normalize();
    auto upn = up.normalize();
    auto left = upn.cross(forward);
    auto trueUp = forward.cross(left);

    auto orientation = ngl::Mat4(left.m_x, left.m_y, left.m_z, 0,
                                 trueUp.m_x, trueUp.m_y, trueUp.m_z, 0,
                                 -forward.m_x, -forward.m_y, -forward.m_z, 0,
                                 0, 0, 0, 1);

    return orientation * ngl::Mat4::translate(-from.m_x, -from.m_y, -from.m_z);  
}