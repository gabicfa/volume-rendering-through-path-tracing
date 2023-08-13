#ifndef CANVAS_H_
#define CANVAS_H_

#include <vector>
#include <ngl/Vec3.h>
#include <memory>

// Represents a 2D canvas, which is used for drawing, storing pixel data, and various image parameters.
class Canvas
{
    public:
        Canvas(size_t _w, size_t _h);
        size_t width() const;
        size_t height() const;
        void samplesPerPixel(int _s);
        int samplesPerPixel() const;
        void maxDepth(int _m);
        int maxDepth() const;
        ngl::Vec3 getPixel(size_t _x, size_t _y) const;
        void setPixel(size_t _x, size_t _y, ngl::Vec3 _colour) const;
        const ngl::Vec3 * getPixelsBuffer() const;
    private:
        // Width of the canvas.
        size_t m_width=0;
        
        // Height of the canvas.
        size_t m_height=0;
        
        // Defines the number of samples taken for each pixel.
        int m_samplesPerPixel;
        
        // Maximum recursive depth.
        int m_maxDepth;
        
        // Pointer to an array of pixel data stored in continuous memory.
        std::unique_ptr<ngl::Vec3 []> m_pixels; 
};

#endif
