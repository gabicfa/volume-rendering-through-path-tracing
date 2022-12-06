#ifndef IMAGE_H_
#define IMAGE_H_

#include <vector>

#include <ngl/AbstractVAO.h>
#include <memory>
#include "Pixel.h"

class Image
{
    public:
        Image(size_t _numPixels);
        void update();
        void render() const;
    private:
        void createPixel(Pixel &io_p);
        std::vector<Pixel> m_pixels;
        std::unique_ptr<ngl::AbstractVAO> m_vao;
};

#endif