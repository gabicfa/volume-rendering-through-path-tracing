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

void defaultScene(Scene &s, Camera &c)
{
    s = Scene(true);
    
    auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(-10.0f, 10.0f, -10.0f));
    s.light(light);
    
    auto t = Transformations::viewTransform(ngl::Vec4(-0.5f, 1.0f, -4.0f),
                                        ngl::Vec4(0.0f, 1.0f, 0.0f),
                                        ngl::Vec4(0.0f, -1.0f, 0.0f));
    c.transform(t);
}

void readFileAndCreateScene(Scene &s, Camera &c)
{
  boost::property_tree::ptree pt;
  boost::property_tree::read_json("../json/input.json", pt);

  // Light attributes
  auto l = pt.get_child("light");
  auto li = l.get_child("intensity");
  auto intensityVector = ngl::Vec3(li.get<float>("r"),li.get<float>("g"),li.get<float>("b"));
  auto lp = l.get_child("position");
  auto positionVector = ngl::Vec4(lp.get<float>("x"),lp.get<float>("y"),lp.get<float>("z"));

  auto light = Light(intensityVector, positionVector);
  s.light(light);


  // Camera attributes
  auto cam = pt.get_child("camera");
  auto fov = cam.get<double>("fieldOfView") * M_PI / 180.0;
  auto from = cam.get_child("from");
  auto to = cam.get_child("to");
  auto up = cam.get_child("up");
  auto t = Transformations::viewTransform(ngl::Vec4(from.get<float>("x"),from.get<float>("y"),from.get<float>("z")),
                                          ngl::Vec4(to.get<float>("x"),-to.get<float>("y"),to.get<float>("z")),
                                          ngl::Vec4(up.get<float>("x"),-up.get<float>("y"),up.get<float>("z")));
  c.fieldOfView(fov);
  c.transform(t);

  //Sphere attributes
  auto spheres = pt.get_child("spheres");
  auto id = 0;
  for (auto& sphere : spheres) 
  {
    auto obj = Sphere(id);
    auto t = ngl::Mat4();
    if(sphere.second.count("translate"))
    {
      auto translate = sphere.second.get_child("translate");
      t = t * ngl::Mat4::translate(translate.get<float>("x"),translate.get<float>("y"),translate.get<float>("z"));
    }
    if(sphere.second.count("scale"))
    {
      auto scale = sphere.second.get_child("scale");
      t = t * ngl::Mat4::scale(scale.get<float>("x"),scale.get<float>("y"),scale.get<float>("z"));
    }

    // Material attributes
    if(sphere.second.count("material"))
    {
      auto mat = sphere.second.get_child("material");
      auto material = Material();

      if(mat.count("specular"))
      {
        material.specular(mat.get<float>("specular"));
      }

      if(mat.count("diffuse"))
      {
        material.diffuse(mat.get<float>("diffuse"));
      }

      if(mat.count("ambient"))
      {
        material.ambient(mat.get<float>("ambient"));
      }

      if(mat.count("shininess"))
      {
        material.shininess(mat.get<float>("shininess"));
      }

      if(mat.count("color"))
      {
        auto color = mat.get_child("color");
        material.color(ngl::Vec3(color.get<float>("r"),color.get<float>("g"),color.get<float>("b")));
      }
      obj.material(material);
    }
    obj.setTransform(t);
    s.addObject(obj);
  }
}

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
  infile.open("../json/input.json");
  if(infile.is_open())
  {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json("../json/input.json", pt);
    if(pt.get<bool>("defaultScene"))
    {
      defaultScene(scene, camera);
    }
    else
    {
      readFileAndCreateScene(scene, camera);
    }
    infile.close();
  }
  else
  {
    defaultScene(scene, camera);
  }

  m_canvas = std::make_unique<Canvas>(camera.render(scene));
  updateTextureBuffer();
  startTimer(10);
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
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
