#include <QMouseEvent>
#include <QGuiApplication>
#include <fstream>
#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <iostream>
#include <cmath>
#include <ngl/Random.h>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>

#include "Scene.h"
#include "Sphere.h"
#include "Utility.h"
#include "Camera.h"
#include "OldMaterial.h"
#include "AreaLight.h"
#include "RendererServices.h"
#include "ObjFile.h"

constexpr size_t TextureWidth = 100;
constexpr size_t TextureHeight = 100;

// const auto aspectRatio = 16.0 / 16.0;
// int TextureWidth = 180;
// int TextureHeight = static_cast<int>(TextureWidth / aspectRatio);

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

void createScene(Scene &scene, Camera &camera, int &fov, ngl::Vec4 &from, ngl::Vec4 to, ngl::Vec4 up,
                ngl::Vec4 &lightCenter, ngl::Vec4 &lightU,ngl::Vec4 &lightV, ngl::Vec3 &lightIntensity, Scene::SceneMode mode)
{
    fov = 90;
    from = ngl::Vec4(0.0f, 2.5f, -8.0f);
    to = ngl::Vec4(0.0f, 4.0f, 0.0f);
    up = ngl::Vec4(0.0f, 1.0f, 0.0f);
    lightCenter = ngl::Vec4(0.0f, 70.0f, 0.0f);
    lightU = ngl::Vec4(1.0f, 0.0f, 0.0f);
    lightV = ngl::Vec4(0.0f, 0.0f, -1.0f);
    lightIntensity = ngl::Vec3(10.0f,10.0f,10.0f);

    scene.chooseScene(mode);

    if (mode == Scene::SceneMode::Scene1)
    {
      from = ngl::Vec4(0.0f, 0.0f, -3.0f);
      to = ngl::Vec4(0.0f, 0.0f, 0.0f);
      lightCenter = ngl::Vec4(0.0f, 0.9f, 0.0f);
      lightIntensity = ngl::Vec3(5.0f,5.0f,5.0f);
      fov = 60;
    }
    if (mode == Scene::SceneMode::Scene2)
    {
      from = ngl::Vec4(0.0f, 2.0f, -5.0f);
      to = ngl::Vec4(0.0f, 5.0f, 0.0f);
      up = ngl::Vec4(0.0f, 1.0f, 0.0f);
      fov = 90;
    }
    if (mode == Scene::SceneMode::Scene3)
    {
      from = ngl::Vec4(0.0f, 2.0f, -5.0f);
      to = ngl::Vec4(0.0f, 5.0f, 0.0f);
      up = ngl::Vec4(0.0f, 1.0f, 0.0f);
      lightCenter = ngl::Vec4(0.0f, 10.0f, 0.0f);
      fov = 60;
    }
    
              
    auto light = AreaLight(lightCenter, lightU, lightV, lightIntensity);
    scene.areaLight(light);
    auto rs = RendererServices(light);
    scene.rs(rs);

    auto t = Transformations::viewTransform(from, to, up);
    camera.transform(t);
    camera.fieldOfView(fov * M_PI / 180);
}

void NGLScene::initializeGL()
{
    // Initialize OpenGL and other settings
    ngl::NGLInit::initialize();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    ngl::ShaderLib::loadShader(TextureShader, "shaders/TextureVertex.glsl", "shaders/TextureFragment.glsl");
    glGenTextures(1, &m_textureID);
    glGenVertexArrays(1, &m_vao);
    
    // Generate our buffer for the texture data

      auto scene = Scene();
      auto camera = Camera(TextureWidth, TextureHeight, M_PI / 2);

      int fov;
      ngl::Vec4 from, to, up, lightPosition, lightU, lightV;
      ngl::Vec3 lightIntensity;

      createScene(scene, camera, fov, from, to, up,
                  lightPosition, lightU, lightV, lightIntensity, Scene::SceneMode::Default);

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
