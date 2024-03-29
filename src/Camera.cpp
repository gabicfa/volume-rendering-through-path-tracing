#include "Camera.h"
#include "Utility.h"
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

Camera::Camera(size_t _h, size_t _v, double _fov) : m_hsize{_h}, m_vsize{_v}, m_fieldOfView{_fov}
{
    this->fieldOfView(m_fieldOfView);
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

void Camera::fieldOfView(double _fov)
{
    m_fieldOfView = _fov;
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
Ray Camera::rayForPixel(double _px, double _py)
{
    auto xoffset = (_px + 0.5) * m_pixelSize;
    auto yoffset = (_py + 0.5) * m_pixelSize;
    
    auto worldX = m_halfWidth - xoffset;
    auto worldY = m_halfHeight - yoffset;

    auto pixel = m_transformation.inverse() * ngl::Vec4(worldX, worldY, -1);
    auto origin = m_transformation.inverse() * ngl::Vec4(0.0f,0.0f,0.0f);
    auto d = pixel - origin;
    auto direction = d;
    if (d.length() > 0)
    {
        direction.normalize();
    }

    return Ray(origin, direction);
}
/// end of Citation

void Camera::transform(ngl::Mat4 _t)
{
    m_transformation = _t;
}

// The `writeColor` function processes a pixel's color after it has been accumulated
// over several samples, using gamma correction for more perceptually linear color changes.

/// @brief The BSDF abstract base class
/// Modified from :
/// Shirley et al. (2023). Ray Tracing: The Next Week [online]. Available from https://raytracing.github.io/books/RayTracingTheNextWeek.html [Accessed 12 August 2023].
ngl::Vec3 Camera::writeColor(ngl::Vec3 pixelColor, int samples_per_pixel) {
    auto r = pixelColor.m_x;
    auto g = pixelColor.m_y;
    auto b = pixelColor.m_z;

    auto scale = 1.0 / samples_per_pixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    return ngl::Vec3(clamp(r, 0.0, 0.999), clamp(g, 0.0, 0.999), clamp(b, 0.0, 0.999));
}
// end of citation

// The `render` function ray-traces the entire scene from the camera's perspective,
// producing an image on a canvas. This process is computationally intensive, 
// so it is parallelized using TBB (Threading Building Blocks) for better performance. 
// TBB's parallel_for divides the rendering task among multiple threads, allowing for faster processing.
Canvas Camera::render(Scene &s)
{
    auto img = Canvas(m_hsize, m_vsize);
    auto samplesPerPixel = img.samplesPerPixel();
    auto maxDepth = img.maxDepth();

    // TBB's parallel_for is used to distribute the pixel rendering task across multiple threads. 
    // The outer loop iterates over rows (y-axis) of pixels, while the inner loop iterates over 
    // columns (x-axis). This ensures that the task of rendering each pixel can be performed in parallel.
    tbb::parallel_for(tbb::blocked_range<int>(0, m_vsize - 1), [&](const tbb::blocked_range<int>& rangeY) {
        for (int y = rangeY.begin(); y != rangeY.end(); ++y) {
            tbb::parallel_for(tbb::blocked_range<int>(0, m_hsize - 1), [&](const tbb::blocked_range<int>& rangeX) {
                for (int x = rangeX.begin(); x != rangeX.end(); ++x) {
                    ngl::Vec3 color(0, 0, 0);
                    for (int sp = 0; sp < samplesPerPixel; ++sp) {
                        auto u = x + randomFloat();
                        auto v = y + randomFloat();
                        auto r = this->rayForPixel(u, v);
                        color += s.pathTrace(r, maxDepth);
                    }

                    auto colorAntialias = writeColor(color, samplesPerPixel);
                    img.setPixel(x, y, colorAntialias);
                }
            });
        }
    });
    std::cout << "FINISHED \n";
    return img;
}
