#include "Camera.h"

Camera::Camera(size_t _h, size_t _v, double _fov) : m_hsize{_h}, m_vsize{_v}, m_fieldOfView{_fov}
{
    auto halfView = tan(m_fieldOfView/2);
    auto aspect = static_cast<float>(m_hsize) / static_cast<float>(m_vsize);

    if(aspect >= 1)
    {
        m_halfWidth = halfView;
        m_halfHeight = halfView / aspect;
    }
    else
    {
        m_halfWidth = halfView * aspect;
        m_halfHeight = halfView;
    }

    m_pixelSize = (m_halfWidth * 2) / m_hsize;
}

size_t Camera::hsize() const
{
    return m_hsize;
}

size_t Camera::vsize() const
{
    return m_vsize;
}

double Camera::fieldOfView() const
{
    return m_fieldOfView;
}

double Camera::halfWidth() const
{
    return m_halfWidth;
}

double Camera::halfHeight() const
{
    return m_halfHeight;
}

ngl::Mat4 Camera::transform() const
{
    return m_transformation;
}

double Camera::pixelSize() const
{
    return m_pixelSize;
}


/// @brief Constructing rays at cameras pixels
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
Ray Camera::rayForPixel(double px, double py)
{
    auto xoffset = (px + 0.5) * m_pixelSize;
    auto yoffset = (py + 0.5) * m_pixelSize;
    
    auto worldX = m_halfWidth - xoffset;
    auto worldY = m_halfHeight - yoffset;

    auto pixel = m_transformation.inverse() * ngl::Vec4(worldX, worldY, -1);
    auto origin = m_transformation.inverse() * ngl::Vec4(0.0f,0.0f,0.0f);
    auto direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}
/// end of Citation

void Camera::transform(ngl::Mat4 _t)
{
    m_transformation = _t;
}

Canvas Camera::render(Scene &s)
{
    auto img = Canvas(m_hsize, m_vsize);
    for (auto y=0; y< m_vsize-1; y++)
    {
        for(auto x=0; x< m_hsize-1; x++)
        {
            auto r = this->rayForPixel(x, y);
            auto color = s.colorAt(r);
            img.setPixel(x, y, color);
        }
    }
    return img;
}
