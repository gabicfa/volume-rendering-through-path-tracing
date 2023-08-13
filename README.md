# Volume Rendering through Path Tracing - Msc Project

## Overall Idea

I developed a Ray Tracer program with the ability to ray-trace spheres. The program uses a simple JSON file to describe the material properties, light, and objects in the scene. The ray-traced image is shown using a OpenGL frame buffer.

## Class Design

![diagram](/images/diagram.png)

## Running the program

To build this program is necessary to install the [NGL](https://github.com/NCCA/NGL) graphics library and the main [Qt](https://www.qt.io/download) development system.

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

The scene is built based on the parameters of the `json/input.json` file. 


## JSON parameters

- If the parameter `defaultScene` is true, the default scene of one sphere will be rendered.
- If the parameter `defaultScene` is false, the rest of the JSON file will be computed to render the scene.

### Light

```
"light" : 
{
    // Point light color
    "intensity": {
        "r": 1.0, 
        "g": 1.0, 
        "b": 1.0
    },
    // Point light position
    "position": {
        "x": -10.0, 
        "y": 10.0, 
        "z": -10.0
    }
}

```

### Camera

```
"camera":
{
    // Camera zoom
    "fieldOfView": 60,
    // Camera position
    "from": {
        "x": 0.0, 
        "y": 1.0, 
        "z": -5.0
    },
    // Where the camera is pointing to
    "to": {
        "x": 0.0, 
        "y": -1.0, 
        "z": 0.0
    },
    // Camera up vector
    "up": {
        "x": 0.0, 
        "y": 1.0, 
        "z": 0.0
    }
}
    
```

### Spheres

```
"spheres":
[{
    //Translate matrix applied to the object
    "translate": {
        "x": 0.0,
        "y": 0.0,
        "z": 8.0
    },
    //Scale matrix applied to the object
    "scale": {
        "x":10.0,
        "y":10.0,
        "z":0.1
    },
    //Material applied to the object
    "material":{
        // Material color (If not defined, the default colour is 1.0, 1.0, 1.0)
        "color":{
            "r": 1.0,
            "g": 0.9,
            "b": 0.9
        },
        // Material specular attribute (If not defined, the default value is 0.9)
        "specular":0.0,
        // Material ambient attribute (If not defined, the default value is 0.1)
        "ambient":0.2,
        // Material diffuse attribute (If not defined, the default value is 0.9)
        "diffuse":0.7,
        // Material shininess attribute (If not defined, the default value is 200.0)
        "shininess":150.0
    }
}]
```

## Future Implementation

I would like to add different primitives to the scene, not only spheres. In the future, I plan to implement planes, cubes, cylinders, cones, and meshes.

## References

[The Ray Tracer Challenge: A Test-Driven Guide to Your First 3D Renderer, Jamis Buck, Pragmatic Bookshelf, March 2019](https://pragprog.com/titles/jbtracer/the-ray-tracer-challenge/)

[An Introduction to Ray Tracing, edited by Andrew Glassner, Morgan Kaufmann, 1989](http://www.realtimerendering.com/raytracing/An-Introduction-to-Ray-Tracing-The-Morgan-Kaufmann-Series-in-Computer-Graphics-.pdf)

[Ray Tracing in One Weekend - The Book Series](https://raytracing.github.io/)

[Ray Tracing Essentials Playlist - NVIDIA Developer](https://youtube.com/playlist?list=PL5B692fm6--sgm8Uiava0IIvUojjFOCSR)

[Ray Tracing - The Cherno](https://youtube.com/playlist?list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl)

[Ray Tracing from the Ground Up, by Kevin Suffern, September 2007](https://www.amazon.com/Ray-Tracing-Ground-Kevin-Suffern/dp/1568812728?tag=realtimerenderin&pldnSite=1)

[Scratchapixel - 3D Rendering for Beginners](https://www.scratchapixel.com/)

[Physically Based Rendaring](https://pbr-book.org/)
