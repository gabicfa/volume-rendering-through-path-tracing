#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <iostream>
#include <ngl/Random.h>

#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Light.h"

// constexpr size_t TextureWidth=1024;
// constexpr size_t TextureHeight=720;

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

  // auto floor = Sphere(1);
  // floor.setTransform(ngl::Mat4::scale(10.0f,0.1f,-10.0f));
  // auto mat1 = Material();
  // mat1.color(ngl::Vec3(1.0f,0.0f,0.0f));
  // mat1.specular(0.0f);
  
  // floor.material(mat1);
  // scene.addObject(floor);

  auto middle = Sphere(2);
  middle.setTransform(ngl::Mat4::translate(-0.5, 1, -0.5));
  auto mat2 = Material();
  mat2.color(ngl::Vec3(0.1f,1.0f,0.5f));
  mat2.diffuse(0.7f);
  mat2.specular(0.3f);
  
  middle.material(mat2);
  scene.addObject(middle);

  auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(1.0f, -1.0f, 10.0f));
  scene.light(light);
  
  auto camera = Camera(TextureWidth, TextureHeight, M_PI/3);
  auto t = Transformations::viewTransform(ngl::Vec4(0.0f, 1.5f, -5.0f),
                                          ngl::Vec4(0.0f, 1.0f, 0.0f),
                                          ngl::Vec4(0.0f, 1.0f, 0.0f));
  camera.transform(t);
  
  m_canvas = std::make_unique<Canvas>(camera.render(scene));
  updateTextureBuffer();
  startTimer(10);
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  updateTextureBuffer();
  update();
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
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw
    update();
}
