#include <QMouseEvent>
#include <QGuiApplication>
#include <fstream>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <iostream>
#include <cmath>
#include <ngl/Random.h>
// #include <boost/property_tree/ptree.hpp>
// #include <boost/property_tree/json_parser.hpp>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>

#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "OldMaterial.h"
#include "Light.h"
#include "ObjFile.h"

// constexpr size_t TextureWidth = 360;
// constexpr size_t TextureHeight = 180;

const auto aspectRatio = 16.0 / 8.0;
const int TextureWidth = 360;
const int TextureHeight = static_cast<int>(TextureWidth / aspectRatio);

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
    s = Scene(true, 1);
    
    auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f, 10.0f, -10.0f));
    s.light(light);
    
    auto t = Transformations::viewTransform(ngl::Vec4(0.0f, 0.0f, -3.0f),
                                        ngl::Vec4(0.0f, 0.0f, 3.0f),
                                        ngl::Vec4(0.0f, 1.0f, 0.0f));
    c.transform(t);
    c.fieldOfView(90 * M_PI / 180);
}

void readFileAndCreateScene(Scene &s, Camera &c, rapidjson::Document &document)
{
    std::ifstream ifs("../json/input.json");
    rapidjson::IStreamWrapper isw(ifs);
    // rapidjson::Document document;
    document.ParseStream(isw);

    // Light attributes
    const auto& l = document["light"];
    const auto& intensity = l["intensity"];
    auto intensityVector = ngl::Vec3(intensity["r"].GetFloat(), intensity["g"].GetFloat(), intensity["b"].GetFloat());
    const auto& position = l["position"];
    auto positionVector = ngl::Vec4(position["x"].GetFloat(), position["y"].GetFloat(), position["z"].GetFloat());

    auto light = Light(intensityVector, positionVector);
    s.light(light);

    // Camera attributes
    const auto& cam = document["camera"];
    auto fov = cam["fieldOfView"].GetDouble() * M_PI / 180.0;
    const auto& from = cam["from"];
    const auto& to = cam["to"];
    const auto& up = cam["up"];
    auto t = Transformations::viewTransform(ngl::Vec4(from["x"].GetFloat(), from["y"].GetFloat(), from["z"].GetFloat()),
                                            ngl::Vec4(to["x"].GetFloat(), to["y"].GetFloat(), to["z"].GetFloat()),
                                            ngl::Vec4(up["x"].GetFloat(), up["y"].GetFloat(), up["z"].GetFloat()));
    c.fieldOfView(fov);
    c.transform(t);

    const auto& file = document["file"].GetString();
    std::cout << "FILE: " << file << "\n";
    ObjFile obj(file);
    auto objs = obj.sceneObjects();
    for (auto &o : objs)
    {
        s.addObject(o);
    }

    // Sphere attributes
    const auto& spheres = document["spheres"];
    auto id = 0;
    for (rapidjson::Value::ConstValueIterator it = spheres.Begin(); it != spheres.End(); ++it)
    {
        const auto& sphere = *it;
        auto obj = std::make_shared<Sphere>(1);

        auto t = ngl::Mat4();
        if (sphere.HasMember("translate"))
        {
            const auto& translate = sphere["translate"];
            t = t * ngl::Mat4::translate(translate["x"].GetFloat(), translate["y"].GetFloat(), translate["z"].GetFloat());
        }
        if (sphere.HasMember("scale"))
        {
            const auto& scale = sphere["scale"];
            t = t * ngl::Mat4::scale(scale["x"].GetFloat(), scale["y"].GetFloat(), scale["z"].GetFloat());
        }

        // OldMaterial attributes
        if (sphere.HasMember("material"))
        {
            const auto& mat = sphere["material"];
            auto material = OldMaterial();

            if (mat.HasMember("specular"))
            {
                material.specular(mat["specular"].GetFloat());
            }

            if (mat.HasMember("diffuse"))
            {
                material.diffuse(mat["diffuse"].GetFloat());
            }

            if (mat.HasMember("ambient"))
            {
                material.ambient(mat["ambient"].GetFloat());
            }

            if (mat.HasMember("shininess"))
            {
                material.shininess(mat["shininess"].GetFloat());
            }

            if (mat.HasMember("color"))
            {
                const auto& color = mat["color"];
                material.color(ngl::Vec3(color["r"].GetFloat(), color["g"].GetFloat(), color["b"].GetFloat()));
            }
            // obj->setOldMaterial(material);
        }
        obj->setTransform(t);
        // s.addObject(obj);
    }
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

    std::ifstream infile("../json/input.json");
    if (infile.is_open())
    {
        rapidjson::IStreamWrapper isw(infile);
        rapidjson::Document document;
        document.ParseStream(isw);

        if (document.HasMember("defaultScene") && document["defaultScene"].IsBool() && document["defaultScene"].GetBool())
        {
            defaultScene(scene, camera);
        }
        else
        {
            readFileAndCreateScene(scene, camera, document);
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
