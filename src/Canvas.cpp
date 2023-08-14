#include "Canvas.h"
#include "Sphere.h"
#include "Utility.h"
#include "Intersection.h"
#include "Config.h"

// Constructor that initializes canvas dimensions and allocates memory for pixel data.
Canvas::Canvas(size_t _w, size_t _h) : m_width{_w}, m_height{_h}
{
    // Allocate memory for pixel data and initialize all pixels to black.
    m_pixels = std::make_unique<ngl::Vec3 []>(m_width*m_height);
    for(size_t i=0; i<m_width*m_height; ++i)
    {
        m_pixels[i]=ngl::Vec3(0.0f, 0.0f, 0.0f);
    }
    // Set default values for samples per pixel and max depth.
    m_samplesPerPixel= SAMPLES_PER_PIXEL;
    m_maxDepth= MAX_DEPTH;
}

size_t Canvas::width() const
{
    return m_width;
}

size_t Canvas::height() const
{
    return m_height;
}

// Sets the number of samples per pixel.
void Canvas::samplesPerPixel(int _s)
{
    m_samplesPerPixel = _s;
}

int Canvas::samplesPerPixel() const
{
    return m_samplesPerPixel;
}

// Sets the maximum depth for recursive algorithms.
void Canvas::maxDepth(int _s)
{
    m_maxDepth = _s;
}

int Canvas::maxDepth() const
{
    return m_maxDepth;
}

// Gets the color of the pixel at specified coordinates by calculating its index.
ngl::Vec3 Canvas::getPixel(size_t _x, size_t _y) const
{
    auto index = (_y*m_width) + _x;
    return m_pixels[index];
}

// Sets the color of the pixel at specified coordinates. Checks for boundary conditions.
void Canvas::setPixel(size_t _x, size_t _y, ngl::Vec3 _colour) const
{
    if(_x>m_width || _y > m_height)
        return;
    auto index = (_y*m_width)+_x;
    m_pixels[index]=_colour;    
}

// Returns the direct pointer to the pixel data.
const ngl::Vec3 * Canvas::getPixelsBuffer() const 
{
    return m_pixels.get();
}
