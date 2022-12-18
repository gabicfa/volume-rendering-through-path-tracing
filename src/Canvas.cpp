#include "Canvas.h"

Canvas::Canvas(size_t _w, size_t _h) : m_width{_w}, m_height{_h}
{
    m_pixels = std::make_unique<ngl::Vec3 []>(m_width*m_height);
    for(size_t i=0; i<m_width*m_height; ++i)
    {
        m_pixels[i]=ngl::Vec3(0.0f, 0.0f, 0.0f);
    }
}

size_t Canvas::width() const
{
    return m_width;
}

size_t Canvas::height() const
{
    return m_height;
}

ngl::Vec3 Canvas::getPixel(size_t _x, size_t _y) const
{
    auto index = (_y*m_width) + _x;
    return m_pixels[index];
}

void Canvas::setPixel(size_t _x, size_t _y, ngl::Vec3 _colour) const
{
    if(_x>m_width || _y > m_height)
        return;
    auto index = (_y*m_width)+_x;
    m_pixels[index]=_colour;    
}

const ngl::Vec3 * Canvas::getPixelsBuffer() const 
{
    return m_pixels.get();
}