# Volume Rendering through Path Tracing - Msc Project

## Overall Idea

I developed a renderer with the ability to path trace a scene. This renderer has the ability to path trace fog-like volumes. It calculates the global Illumination based on the PBR theory. The program has six pre-defined scenes that the user can choose from. The final image is shown using an OpenGL frame buffer.

## Class Design

![diagram](/images/diagram.png)

## Running the program

To build this program is necessary to install the [NGL](https://github.com/NCCA/NGL) graphics library, the main [Qt](https://www.qt.io/download) development system and Intel's TBB.

The program is built with CMake. To build the program:

Windows
```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=~/NGL ..
cmake --build .
```

Mac Linux
```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=~/NGL ..
make 
```

There are six possible scenes to render in this render. You can choose between them by setting the variables in the sceneFile.txt

## SCENES PARAMETERS

The sceneFile.txt file dictates what scene is going to be rendered and the configurations of the rendering process. The file has the following structure:

### sceneFile.txt

```
SAMPLES_PER_PIXEL = 10;
MAX_DEPTH = 6;
NUM_LIGHT_SAMPLES = 1;
NUM_WIDTH = 50;
NUM_HEIGHT = 50;
SCENE = 0;
```

#### SAMPLES_PER_PIXEL
This parameter dictates the number of rays that will be sent through each pixel in the image during the rendering process. More samples often result in smoother and more accurate color representation, especially in scenes with complex lighting. However, higher values can significantly increase the render time.

#### MAX_DEPTH 
`MAX_DEPTH` represents the maximum number of times a ray can bounce off surfaces in the scene. When a ray bounces off a surface, it might generate additional rays (reflected, refracted, etc.), and this parameter ensures the process doesn't continue indefinitely. A deeper depth allows for more interactions and can lead to more realistic images, but can also increase computation time.

#### NUM_LIGHT_SAMPLES
This parameter specifies the number of random sample rays sent towards light sources to compute soft shadows and illumination. Higher numbers can provide more accurate shadow and lighting representation at the expense of increased computational time.

#### NUM_WIDTH
This parameter sets the width (in terms of number of pixels) of the rendered image. Increasing this value will provide a more detailed and wider view of the scene but will also take longer to render.

#### NUM_HEIGHT
Similar to `NUM_WIDTH`, this parameter sets the height (in terms of number of pixels) of the rendered image. A larger value offers a more detailed and taller view of the scene, but will also require more computation time to render.

#### SCENE
Chooses one of the six possible scenes. They are:

    1 - A traditional Cornell Box
    2 - A teapot
    3 - A specular sphere next to a fog sphere, next to a diffuse pyramid
    4 - A Cornell Box with a specular ball in the centre
    5 - A colourful floor with a heterogeneous fog sphere
    0 - A colourful floor with a homogeneous fog sphere

## Future Implementation

I would like to add different types of volumes, like single-scattering (smoke) and multi-scattering (clouds) ones. Also, the rendering time is quite long, I need to work on optimizations.
