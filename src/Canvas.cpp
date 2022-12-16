#include "Canvas.h"
#include <ngl/Random.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <OpenImageIO/imageio.h>

// Canvas::Canvas()
// {
//     m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
// }

Canvas::Canvas(size_t _w, size_t _h) : m_width{_w}, m_height{_h}
{
    m_pixels = std::make_unique<ngl::Vec3 []>(m_width*m_height);
    for(size_t i=0; i<m_width*m_height; ++i)
    {
        m_pixels[i]=ngl::Vec3(1.0f, 0.0f, 0.0f);
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

bool Canvas::save(std::string_view _fname) const
{
    bool success=false;
    using namespace OIIO;
    auto out = ImageOutput::create(_fname.data());
    if(!out)
    {
        return false;
    }
    ImageSpec spec(m_width,m_height,3,TypeDesc::FLOAT);
    success = out->open(_fname.data(),spec);
    success = out->write_image(TypeDesc::FLOAT,m_pixels.get());
    success = out->close();
    return success;
}


Canvas::Canvas(size_t _numPixels)
{
    m_pixels_vector.resize(_numPixels);
    for(auto &p : m_pixels_vector)
    {
        auto position = ngl::Vec3(5.0f, 0.0f, 0.0f);
        auto colour = ngl::Vec3(1.0f, 0.0f, 1.0f);
        writePixel(p, position, colour);
    }
    m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
}

void Canvas::createPixel(ngl::Vec3 _position, ngl::Vec3 _colour)
{
    Pixel p;
    p.position = _position;
    p.colour = _colour;
    m_pixels_vector.push_back(p);
}

void Canvas::writePixel(Pixel &io_p, ngl::Vec3 _position, ngl::Vec3 _colour)
{
    io_p.position = _position;
    // io_p.colour=ngl::Random::getRandomColour3();
    io_p.colour = _colour;
}


std::unique_ptr<ngl::Vec3> Canvas::getPixels() const
{
    return m_pixels;
}

void Canvas::update()
{
    // std::cout<<"update\n";
}

void Canvas::render() const
{
    // std::cout<<"render\n";
    glPointSize(20);
    m_vao->bind();
    m_vao->setData(ngl::SimpleVAO::VertexData(m_pixels_vector.size()*sizeof(Pixel), m_pixels_vector[0].position.m_x));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Pixel),0);
    m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Pixel),3);
    m_vao->setNumIndices(m_pixels_vector.size());
    m_vao->draw();
    m_vao->unbind();
}