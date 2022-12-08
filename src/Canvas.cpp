#include "Canvas.h"
#include <ngl/Random.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>

Canvas::Canvas()
{
    m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
}

Canvas::Canvas(size_t _numPixels)
{
    m_pixels.resize(_numPixels);
    for(auto &p : m_pixels)
    {
        auto position = ngl::Vec3(0.0f, 0.0f, 0.0f);
        auto colour = ngl::Vec3(1.0f, 0.0f, 0.0f);
        writePixel(p, position, colour);
    }
    m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
}

void Canvas::createPixel(ngl::Vec3 _position, ngl::Vec3 _colour)
{
    Pixel p;
    p.position = _position;
    p.colour = _colour;
    m_pixels.push_back(p);
}

void Canvas::writePixel(Pixel &io_p, ngl::Vec3 _position, ngl::Vec3 _colour)
{
    io_p.position = _position;
    // io_p.colour=ngl::Random::getRandomColour3();
    io_p.colour = _colour;
}


std::vector<Pixel> Canvas::getPixels() const
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
    m_vao->setData(ngl::SimpleVAO::VertexData(m_pixels.size()*sizeof(Pixel), m_pixels[0].position.m_x));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Pixel),0);
    m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Pixel),3);
    m_vao->setNumIndices(m_pixels.size());
    m_vao->draw();
    m_vao->unbind();
}