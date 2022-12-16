#ifndef CANVAS_H_
#define CANVAS_H_

#include <vector>
#include <ngl/Vec3.h>
#include <ngl/AbstractVAO.h>
#include <memory>
#include "Pixel.h"

class Canvas
{
    public:
        Canvas() = default;
        Canvas(size_t _w, size_t _h);
        size_t width() const;
        size_t height() const;
        ngl::Vec3 getPixel(size_t _x, size_t _y) const;
        std::unique_ptr<ngl::Vec3> getPixels() const;
        void setPixel(size_t _x, size_t _y, ngl::Vec3 _colour) const;
        bool save(std::string_view _fname) const;
        Canvas(size_t _numPixels);
        void update();
        void render() const;
        void createPixel(ngl::Vec3 _position, ngl::Vec3 _colour);
    private:
        size_t m_width=0;
        size_t m_height=0;
        void writePixel(Pixel &io_p, ngl::Vec3 _position, ngl::Vec3 _colour);
        std::vector<Pixel> m_pixels_vector;
        std::unique_ptr<ngl::AbstractVAO> m_vao;
        std::unique_ptr<ngl::Vec3 []> m_pixels;
};

#endif