#ifndef CANVAS_H_
#define CANVAS_H_

#include <vector>

#include <ngl/AbstractVAO.h>
#include <memory>
#include "Pixel.h"

class Canvas
{
    public:
        Canvas();
        Canvas(size_t _numPixels);
        void update();
        void render() const;
        void createPixel(ngl::Vec3 _position, ngl::Vec3 _colour);
        std::vector<Pixel> getPixels() const;
    private:
        void writePixel(Pixel &io_p, ngl::Vec3 _position, ngl::Vec3 _colour);
        std::vector<Pixel> m_pixels;
        std::unique_ptr<ngl::AbstractVAO> m_vao;
};

#endif