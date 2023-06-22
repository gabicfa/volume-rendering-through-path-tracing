#ifndef CAMERA_H_
#define CAMERA_H_

#include "Transformations.h"
#include "Ray.h"
#include "Canvas.h"
#include "Scene.h"

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
        Canvas render(Scene &s);
    private:
        size_t m_hsize;
        size_t m_vsize;
        double m_fieldOfView;
        ngl::Mat4 m_transformation = ngl::Mat4();
        float m_pixelSize;
        float m_halfWidth;
        float m_halfHeight;
};

#endif