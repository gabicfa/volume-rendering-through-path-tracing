cmake_minimum_required(VERSION 3.12)
#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for CMAKE_TOOLCHAIN_FILE and this must point to where
# vcpkg.cmake is in the University this is set in your .bash_profile to
# export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
# to build see the NGL instructions 
# Windows :- mkdir build; cd build ; cmake -DCMAKE_PREFIX_PATH=~/NGL/ .. ; cmake --build . 
# Linux / Mac mkdir build; cd build; cmake -DCMAKE_PREFIX_PATH~/NGL/ .. ; make
#-------------------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# Name of the project
project(RayTracerBuild)
# This is the name of the Exe change this and it will change everywhere
set(TargetName RayTracer)
# Find Intel TBB package
find_package(TBB CONFIG REQUIRED)
# This will include the file NGLConfig.cmake, you need to add the location to this either using
# -DCMAKE_PREFIX_PATH=~/NGL or as a system environment variable. 
find_package(NGL CONFIG REQUIRED)
# Instruct CMake to run moc automatically when needed (Qt projects only)
set(CMAKE_AUTOMOC ON)
# find Qt libs
# find Qt libs first we check for Version 6
find_package(Qt6 COMPONENTS OpenGL Widgets QUIET )
if ( Qt6_FOUND )
    message("Found Qt6 Using that")
else()
    message("Found Qt5 Using that")
    find_package(Qt5 COMPONENTS OpenGL Widgets REQUIRED)
endif()

# use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Add all header files inside the /include/bsdfs/ folder
file(GLOB BSDF_HEADERS "include/bsdfs/*.h")

# Add all source files inside the /src/bsdfs/ folder
file(GLOB BSDF_SOURCES "src/bsdfs/*.cpp")

# Add all header files inside the /include/volumes/ folder
file(GLOB VOLUMES_HEADERS "include/volumes/*.h")

# Add all source files inside the /src/volumes/ folder
file(GLOB VOLUMES_SOURCES "src/volumes/*.cpp")

# Add all header files inside the /include/materials/ folder
file(GLOB MATERIALS_HEADERS "include/materials/*.h")

# Add all source files inside the /src/materials/ folder
file(GLOB MATERIALS_SOURCES "src/materials/*.cpp")

# Set the name of the executable we want to build
add_executable(${TargetName})

# Add NGL include path
include_directories(include $ENV{HOME}/NGL/include)
target_sources(${TargetName} PRIVATE ${PROJECT_SOURCE_DIR}/src/main.cpp  
			${PROJECT_SOURCE_DIR}/src/NGLScene.cpp  
            ${PROJECT_SOURCE_DIR}/src/Canvas.cpp 
            ${PROJECT_SOURCE_DIR}/src/Ray.cpp 
            ${PROJECT_SOURCE_DIR}/src/Sphere.cpp 
            ${PROJECT_SOURCE_DIR}/src/Intersection.cpp 
            ${PROJECT_SOURCE_DIR}/src/Light.cpp 
            ${PROJECT_SOURCE_DIR}/src/Scene.cpp
            ${PROJECT_SOURCE_DIR}/src/Transformations.cpp
            ${PROJECT_SOURCE_DIR}/src/Camera.cpp
			${PROJECT_SOURCE_DIR}/src/NGLSceneMouseControls.cpp
            ${PROJECT_SOURCE_DIR}/src/Group.cpp
            ${PROJECT_SOURCE_DIR}/src/TestShape.cpp
            ${PROJECT_SOURCE_DIR}/src/Shape.cpp
            ${PROJECT_SOURCE_DIR}/src/Triangle.cpp
            ${PROJECT_SOURCE_DIR}/src/ObjFile.cpp
            ${PROJECT_SOURCE_DIR}/src/Computation.cpp
            ${PROJECT_SOURCE_DIR}/src/Perlin.cpp
            ${PROJECT_SOURCE_DIR}/include/NGLScene.h
            ${PROJECT_SOURCE_DIR}/include/Canvas.h  
            ${PROJECT_SOURCE_DIR}/include/Ray.h 
            ${PROJECT_SOURCE_DIR}/include/Sphere.h 
            ${PROJECT_SOURCE_DIR}/include/Intersection.h
            ${PROJECT_SOURCE_DIR}/include/Light.h
            ${PROJECT_SOURCE_DIR}/include/Scene.h
            ${PROJECT_SOURCE_DIR}/include/Computation.h
            ${PROJECT_SOURCE_DIR}/include/Transformations.h
            ${PROJECT_SOURCE_DIR}/include/Camera.h
            ${PROJECT_SOURCE_DIR}/include/Shape.h
            ${PROJECT_SOURCE_DIR}/include/Group.h
            ${PROJECT_SOURCE_DIR}/include/TestShape.h
            ${PROJECT_SOURCE_DIR}/include/Triangle.h
            ${PROJECT_SOURCE_DIR}/include/ObjFile.h
            ${PROJECT_SOURCE_DIR}/include/Utility.h
            ${PROJECT_SOURCE_DIR}/include/Material.h
            ${PROJECT_SOURCE_DIR}/include/BSDF.h
            ${PROJECT_SOURCE_DIR}/include/Volume.h
            ${PROJECT_SOURCE_DIR}/include/Perlin.h
            ${PROJECT_SOURCE_DIR}/src/RendererServices.cpp
            ${PROJECT_SOURCE_DIR}/include/RendererServices.h
            ${PROJECT_SOURCE_DIR}/src/AreaLight.cpp
            ${PROJECT_SOURCE_DIR}/include/AreaLight.h
            ${PROJECT_SOURCE_DIR}/include/Config.h
            ${PROJECT_SOURCE_DIR}/src/Config.cpp
            
            # Add the header files from /include/bsdfs/
            ${BSDF_HEADERS}

            # Add the source files from /src/bsdfs/
            ${BSDF_SOURCES}

            # Add the header files from /include/volumes/
            ${VOLUMES_HEADERS}

            # Add the source files from /src/volumes/
            ${VOLUMES_SOURCES}

            # Add the header files from /include/materials/
            ${MATERIALS_HEADERS}

            # Add the source files from /src/materials/
            ${MATERIALS_SOURCES}
)

target_link_libraries(${TargetName} PRIVATE Qt::Widgets Qt::OpenGL NGL TBB::tbb TBB::tbbmalloc)

add_custom_target(${TargetName}CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    ${PROJECT_BINARY_DIR}/shaders
)
ADD_DEPENDENCIES(${TargetName} ${TargetName}CopyShaders)

add_custom_target(${TargetName}CopyFilesFolder ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/files
    ${CMAKE_BINARY_DIR}/files
)
ADD_DEPENDENCIES(${TargetName} ${TargetName}CopyFilesFolder)

# Add testing stuff
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(RayTracerTests)
include_directories(include)
target_sources(RayTracerTests PRIVATE tests/CanvasTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Canvas.cpp 
    ${PROJECT_SOURCE_DIR}/include/Canvas.h
    tests/RayTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Ray.cpp
    ${PROJECT_SOURCE_DIR}/include/Ray.h
    tests/SphereTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Sphere.cpp 
    ${PROJECT_SOURCE_DIR}/include/Sphere.h
    tests/IntersectionTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Intersection.cpp 
    ${PROJECT_SOURCE_DIR}/include/Intersection.h
    tests/LightTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Light.cpp 
    ${PROJECT_SOURCE_DIR}/include/Light.h
    tests/SceneTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Scene.cpp 
    ${PROJECT_SOURCE_DIR}/include/Scene.h
    tests/TransformationsTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Transformations.cpp 
    ${PROJECT_SOURCE_DIR}/include/Transformations.h
    tests/CameraTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Camera.cpp 
    ${PROJECT_SOURCE_DIR}/include/Camera.h
    tests/GroupTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Group.cpp 
    ${PROJECT_SOURCE_DIR}/include/Group.h
    ${PROJECT_SOURCE_DIR}/include/TestShape.h
    ${PROJECT_SOURCE_DIR}/src/TestShape.cpp 
    tests/ShapeTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Shape.cpp 
    ${PROJECT_SOURCE_DIR}/include/Shape.h 
    tests/TriangleTests.cpp
    ${PROJECT_SOURCE_DIR}/src/Triangle.cpp 
    ${PROJECT_SOURCE_DIR}/include/Triangle.h 
    tests/ObjFileTests.cpp
    ${PROJECT_SOURCE_DIR}/src/ObjFile.cpp 
    ${PROJECT_SOURCE_DIR}/include/ObjFile.h 
    ${PROJECT_SOURCE_DIR}/include/Material.h
    ${PROJECT_SOURCE_DIR}/include/BSDF.h
    ${PROJECT_SOURCE_DIR}/include/Volume.h
    ${PROJECT_SOURCE_DIR}/include/Perlin.h
    ${PROJECT_SOURCE_DIR}/src/Perlin.cpp
    ${PROJECT_SOURCE_DIR}/src/Computation.cpp
    ${PROJECT_SOURCE_DIR}/include/Utility.h
    ${PROJECT_SOURCE_DIR}/src/RendererServices.cpp
    ${PROJECT_SOURCE_DIR}/include/RendererServices.h
    ${PROJECT_SOURCE_DIR}/src/AreaLight.cpp
    ${PROJECT_SOURCE_DIR}/include/AreaLight.h
    ${PROJECT_SOURCE_DIR}/include/Config.h
    ${PROJECT_SOURCE_DIR}/src/Config.cpp

    # Add the header files from /include/bsdfs/
    ${BSDF_HEADERS}

    # Add the source files from /src/bsdfs/
    ${BSDF_SOURCES}

    # Add the header files from /include/volumes/
    ${VOLUMES_HEADERS}

    # Add the source files from /src/volumes/
    ${VOLUMES_SOURCES}

    # Add the header files from /include/materials/
    ${MATERIALS_HEADERS}

    # Add the source files from /src/materials/
    ${MATERIALS_SOURCES}
)
target_link_libraries(RayTracerTests PRIVATE GTest::gtest GTest::gtest_main TBB::tbb TBB::tbbmalloc)
gtest_discover_tests(RayTracerTests)
