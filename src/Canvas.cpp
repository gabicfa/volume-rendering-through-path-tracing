#include "Canvas.h"
#include "Sphere.h"
#include "Intersection.h"

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

void Canvas::drawScene()
{
    auto origin = ngl::Vec4(0.0f,0.0f,-5.0f);
    auto wallZ = 5.0f;

    auto wallSizeX = 7.0f;
    auto wallSizeY = 7.0f;

    auto pixelSizeX = wallSizeX / m_width;
    auto halfX = wallSizeX/2;
    
    auto pixelSizeY = wallSizeY / m_height;
    auto halfY = wallSizeY/2;

    auto color = ngl::Vec3(1.0f,0.0f,0.0f);
    auto shape = Sphere(1);
    auto m = ngl::Mat4::scale(0.5f,1.0f,1.0f);
    shape.setTransform(m);

    for (auto y=0; y<m_width-1; y++)
    {
        auto worldY = halfY - pixelSizeY * y;
        for (auto x=0; x<m_width-1; x++)
        {
            auto worldX = -halfX + pixelSizeX * x;
            auto position = ngl::Vec4(worldX, worldY, wallZ);
            auto direction = position - origin;
            auto r = Ray(origin, direction.normalize());
            auto xs = shape.intersect(r);
            auto i = Intersection::hit(xs);
            Intersection empty = Intersection();
            if (i != empty)
            {
                setPixel(x, y, color);
            }
        }
    }
}