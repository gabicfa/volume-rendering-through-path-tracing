#include <cstdlib>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <cmath>


inline double randomDouble() 
{
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) 
{
    return min + (max-min)*randomDouble();
}

inline float randomFloat() 
{
    return rand() / (RAND_MAX + 1.0);
}

inline float randomFloat(float min, float max) 
{
    return min + (max-min)*randomFloat();
}

inline int randomInt(int min, int max)  
{
    return min + rand() % (( max + 1 ) - min);
}

inline float clamp(float x, float min, float max) 
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline ngl::Vec4 randomVec4() 
{
    return ngl::Vec4(randomFloat(), randomFloat(), randomFloat());
}

inline ngl::Vec4 randomVec4(float min, float max) 
{
    return ngl::Vec4(randomFloat(min,max), randomFloat(min,max), randomFloat(min,max));
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

inline bool near_zero(const ngl::Vec4& _vec) {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(_vec.m_x < s) && (fabs(_vec.m_y) < s) && (_vec.m_z) < s);
}

inline bool isBlack(ngl::Vec3 L)
{
    const float epsilon = 1e-4f;
    return std::abs(L.m_x) < epsilon && std::abs(L.m_y) < epsilon && std::abs(L.m_z) < epsilon;
}

inline float channelAvg(const ngl::Vec3 &vec)
{
    return (vec.m_x + vec.m_y + vec.m_z) / 3.0;
}
inline ngl::Vec3 refract(const ngl::Vec3& uv, const ngl::Vec3& n, float etai_over_etat) {
    auto cos_theta = fmin(-uv.dot(n), 1.0);
    ngl::Vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    ngl::Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.lengthSquared())) * n;
    return r_out_perp + r_out_parallel;
}
