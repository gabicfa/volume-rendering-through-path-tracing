#ifndef CAMERA_H_
#define CAMERA_H_

#include "Transformations.h"
#include "Ray.h"
#include "Canvas.h"
#include "Scene.h"

// The Camera class defines the observer's viewpoint in the 3D scene.
// It defines the viewing volume, resolution, and orientation in the world space. 
// It also provides utilities to generate rays that shoot from the camera into the scene 
// and to render the resulting image to a canvas.
class Camera
{
    public:
        Camera() = default;
        Camera(size_t _h, size_t _v, double _fov);
        size_t hsize() const;
        size_t vsize() const;
        double fieldOfView() const;
        void fieldOfView(double _fov);
        void transform(ngl::Mat4 _t);
        ngl::Mat4 transform() const;
        double pixelSize() const;
        double halfWidth() const;
        double halfHeight() const;
        Ray rayForPixel(double _px, double _py);
        ngl::Vec3 writeColor(ngl::Vec3 pixelColor, int samples_per_pixel);
        Canvas render(Scene &s);
    private:
        size_t m_hsize;  // Horizontal size
        size_t m_vsize;  // Vertical size
        double m_fieldOfView;  // Field of view
        ngl::Mat4 m_transformation = ngl::Mat4();  // Transformation matrix for camera orientation
        float m_pixelSize;  // Size of a pixel in world space units
        float m_halfWidth;  // Half width of the camera's viewing plane
        float m_halfHeight;  // Half height of the camera's viewing plane
};

#endif
