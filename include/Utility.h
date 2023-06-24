#include <cstdlib>
#include <ngl/Vec3.h>
#include "Sphere.h"

inline double randomDouble() {
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    return min + (max-min)*randomDouble();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline ngl::Vec4 randomVec4() {
    return ngl::Vec4(randomDouble(), randomDouble(), randomDouble());
}

inline ngl::Vec4 randomVec4(double min, double max) {
    return ngl::Vec4(randomDouble(min,max), randomDouble(min,max), randomDouble(min,max));
}