#include "Transformations.h"

/// @brief builds camera transformation matrix
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 

ngl::Mat4 Transformations::viewTransform(const ngl::Vec4& from, const ngl::Vec4& to, const ngl::Vec4& up)
{
    auto _up = up;
    auto forward = (to - from).normalize();
    auto upn = _up.normalize();
    auto left = forward.cross(upn);
    auto trueUp = forward.cross(left);

    ngl::Mat4 orientation(left.m_x, left.m_y, left.m_z, 0.0f,
                          trueUp.m_x, trueUp.m_y, trueUp.m_z, 0.0f,
                          -forward.m_x, -forward.m_y, -forward.m_z, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f);
    ngl::Mat4 translation = ngl::Mat4::translate(-from.m_x, -from.m_y, -from.m_z);

    return orientation * translation;
}