#include <QMouseEvent>
#include <QGuiApplication>
#include <fstream>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <iostream>
#include <cmath>
#include <ngl/Random.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Light.h"

constexpr size_t TextureWidth = 720;
constexpr size_t TextureHeight = 360;

NGLScene::NGLScene()
{
  setTitle("Ray Tracer NGL");
}

NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL\n";
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

constexpr auto TextureShader="TextureShader";

void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  ngl::ShaderLib::loadShader(TextureShader,"shaders/TextureVertex.glsl","shaders/TextureFragment.glsl");
  glGenTextures(1, &m_textureID);
  glGenVertexArrays(1,&m_vao);
  // Generate our buffer for the texture data

  auto scene = Scene();
  auto camera = Camera(TextureWidth, TextureHeight, M_PI/2);
  
  std::ifstream infile;
  infile.open("input.json");
  if(infile.is_open())
  {
    readFile(scene, camera);
  }
  else
  {
    scene = Scene(true);
    
    auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(-10.0f, 10.0f, -10.0f));
    scene.light(light);
    
    auto t = Transformations::viewTransform(ngl::Vec4(-0.5f, 1.0f, -4.0f),
                                        ngl::Vec4(0.0f, 1.0f, 0.0f),
                                        ngl::Vec4(0.0f, -1.0f, 0.0f));
    camera.transform(t);
  }

  m_canvas = std::make_unique<Canvas>(camera.render(scene));
  updateTextureBuffer();
  startTimer(10);
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
}

void NGLScene::readFile(Scene &s, Camera &c)
{
  boost::property_tree::ptree pt;
  boost::property_tree::read_json("input.json", pt);

  auto l = pt.get_child("light");
  auto li = l.get_child("intensity");
  auto intensityVector = ngl::Vec3(li.get<float>("r"),li.get<float>("g"),li.get<float>("b"));
  auto lp = l.get_child("position");
  auto positionVector = ngl::Vec4(lp.get<float>("x"),lp.get<float>("y"),lp.get<float>("z"));

  auto light = Light(intensityVector, positionVector);
  s.light(light);

  auto cam = pt.get_child("camera");
  auto fov = cam.get<double>("fieldOfView") * M_PI / 180.0;
  auto from = cam.get_child("from");
  auto to = cam.get_child("to");
  auto up = cam.get_child("up");
  auto t = Transformations::viewTransform(ngl::Vec4(from.get<float>("x"),from.get<float>("y"),from.get<float>("z")),
                                          ngl::Vec4(to.get<float>("x"),to.get<float>("y"),to.get<float>("z")),
                                          ngl::Vec4(up.get<float>("x"),-up.get<float>("y"),up.get<float>("z")));
  c.fieldOfView(fov);
  c.transform(t);

  auto floor = Sphere(1);
  floor.setTransform(ngl::Mat4::scale(10.0f,0.01f,10.0f));
  auto mat1 = Material();
  mat1.color(ngl::Vec3(1.0f, 0.9f, 0.9f));
  mat1.specular(0.0f);
  
  floor.material(mat1);
  s.addObject(floor);

  auto wall = Sphere(2);
  wall.setTransform(ngl::Mat4::translate(0.0f, 0.0f, 8.0f) * ngl::Mat4::scale(10.0f,10.0f,0.1f));
  wall.material(mat1);
  s.addObject(wall);

  auto middle = Sphere(3);
  middle.setTransform(ngl::Mat4::translate(-0.5f, 1.0f, 0.5f));
  auto mat2 = Material();
  mat2.color(ngl::Vec3(0.1f,1.0f,0.5f));
  mat2.diffuse(0.7f);
  mat2.specular(0.3f);
  
  middle.material(mat2);
  s.addObject(middle);

  auto right = Sphere(4);
  right.setTransform(ngl::Mat4::translate(1.5f, 0.5f, -0.5f) * ngl::Mat4::scale(0.5f,0.25f,0.5f));
  auto mat3 = Material();
  mat3.color(ngl::Vec3(1.0f,0.0f,1.0f));
  mat3.diffuse(0.7f);
  mat3.specular(0.3f);
  
  right.material(mat3);
  s.addObject(right);

  auto left = Sphere(6);
  left.setTransform(ngl::Mat4::translate(-1.5f, 0.33f, -0.75f) * ngl::Mat4::scale(0.33f, 0.33f, 0.33f));
  auto mat4 = Material();
  mat4.color(ngl::Vec3(1.0f, 0.8f, 0.1f));
  mat4.diffuse(0.7f);
  mat4.specular(0.3f);
  
  left.material(mat4);
  s.addObject(left);
}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  // grab an instance of the shader manager
  ngl::ShaderLib::use(TextureShader);
  glBindVertexArray(m_vao);
  glBindTexture(GL_TEXTURE_2D,m_textureID);
  glDrawArrays(GL_TRIANGLES,0,3);
  glBindVertexArray(0);
}

void NGLScene::updateTextureBuffer()
{
  glBindTexture(GL_TEXTURE_2D, m_textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureWidth, TextureHeight, 0, GL_RGB, GL_FLOAT, m_canvas->getPixelsBuffer());
  glGenerateMipmap(GL_TEXTURE_2D); //  Allocate the mipmaps
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  break;
  default : break;
  }
  // finally update the GLWindow and re-draw
    update();
}
