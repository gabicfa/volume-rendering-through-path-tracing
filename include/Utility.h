#include <cstdlib>
#include <ngl/Vec3.h>
#include <cmath>

inline double randomDouble() 
{
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) 
{
    return min + (max-min)*randomDouble();
}

inline double clamp(double x, double min, double max) 
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline ngl::Vec4 randomVec4() 
{
    return ngl::Vec4(randomDouble(), randomDouble(), randomDouble());
}

inline ngl::Vec4 randomVec4(double min, double max) 
{
    return ngl::Vec4(randomDouble(min,max), randomDouble(min,max), randomDouble(min,max));
}

inline ngl::Vec4 unitVector(const ngl::Vec4& vec)
{
    float length = vec.length();
    if (length != 0)
        return vec / length;
    else
        return vec;
}

inline ngl::Vec4 randomInUnitSphere() {
    while (true) {
        auto p = randomVec4(-1,1);
        if (p.length() >= 1) continue;
        return p;
    }
}

inline ngl::Vec4 randomUnitVector()
{
    return unitVector(randomInUnitSphere());
}

inline ngl::Vec4 randomInHemisphere(const ngl::Vec4& _normal) {
    ngl::Vec4 inUnitSphere = randomInUnitSphere();
    if (inUnitSphere.dot(_normal) > 0.0) 
        return inUnitSphere;
    else
        return -inUnitSphere;
}

inline bool near_zero(const ngl::Vec4& _vec) {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(_vec.m_x < s) && (fabs(_vec.m_y) < s) && (_vec.m_z) < s);
}