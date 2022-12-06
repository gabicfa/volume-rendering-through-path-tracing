#include "Image.h"
#include <ngl/Random.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>

Image::Image(size_t _numPixels)
{
    m_pixels.resize(_numPixels);
    for(auto &p : m_pixels)
    {
        createPixel(p);
    }
    m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
}

void Image::createPixel(Pixel &io_p)
{
    io_p.position.set(0.0f,0.0f,0.0f);
    // io_p.colour=ngl::Random::getRandomColour3();
    io_p.position.set(1.0f,0.0f,0.0f);
    std::cout<<"colour X: " << io_p.colour.m_x << "\n";
}

void Image::update()
{
    std::cout<<"update\n";
}

void Image::render() const
{
    std::cout<<"render\n";
    glPointSize(20);
    m_vao->bind();
    m_vao->setData(ngl::SimpleVAO::VertexData(m_pixels.size()*sizeof(Pixel), m_pixels[0].position.m_x));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Pixel),0);
    m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Pixel),3);
    m_vao->setVertexAttributePointer(2,1,GL_FLOAT,sizeof(Pixel),9);
    m_vao->setNumIndices(m_pixels.size());
    m_vao->draw();
    m_vao->unbind();

}