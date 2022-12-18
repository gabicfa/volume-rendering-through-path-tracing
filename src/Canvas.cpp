#include "Canvas.h"


Canvas::Canvas(size_t _w, size_t _h) : m_width{_w}, m_height{_h}
{
    glGenTextures(1, &m_textureID);
    glGenVertexArrays(1,&m_vao);
    m_pixels = std::make_unique<ngl::Vec3 []>(m_width*m_height);
    for(size_t i=0; i<m_width*m_height; ++i)
    {
        m_pixels[i]=ngl::Vec3(1.0f, 1.0f, 1.0f);
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

void Canvas::update()
{
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_FLOAT, m_pixels.get());
    glGenerateMipmap(GL_TEXTURE_2D); //  Allocate the mipmaps
}

void Canvas::render() const
{
    glBindVertexArray(m_vao);
    glBindTexture(GL_TEXTURE_2D,m_textureID);
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindVertexArray(0);
}