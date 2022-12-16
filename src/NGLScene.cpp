#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <iostream>

constexpr size_t TextureWidth=1024;
constexpr size_t TextureHeight=720;

NGLScene::NGLScene()
{
  setTitle("Ray Tracer NGL");
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  glDeleteTextures(1, &m_textureID);
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_project = ngl::perspective(45.0f, static_cast<float>(_w) / _h, 0.05f, 350.0f);
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

  // MVP is the model view project uiform
  // Colour 4floats

  m_view = ngl::lookAt({10,10,10},{0,0,0},{0,1,0});
  m_project = ngl::perspective(45.0f, 1.0f,0.01f,50.0f);
  
  // Need a vertex array to call draw arrays
  // this will have no buffers
  glGenVertexArrays(1,&m_vao);
  // Now generate a texture
  glGenTextures(1, &m_textureID);
  // Generate our buffer for the texture data
  
  Canvas canvas(500, 500);
  auto colour = ngl::Vec3(1.0f, 1.0f, 1.0f);
  canvas.setPixel(250, 250, colour);
  
  m_buffer=canvas.getPixels();
  canvas.save("ImagePlayground.jpg");
  clearBuffer();
  updateTextureBuffer();

  startTimer(10);
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  update();
}



void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  // m_canvas->render();
  // grab an instance of the shader manager
  ngl::ShaderLib::use(TextureShader);
  // Draw screen Tri with bound Texture
  glBindVertexArray(m_vao);
  glBindTexture(GL_TEXTURE_2D,m_textureID);
  glDrawArrays(GL_TRIANGLES,0,3);
  glBindVertexArray(0);
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
