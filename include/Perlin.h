#ifndef PERLIN_H
#define PERLIN_H
#include <ngl/Vec3.h>

// The Perlin class generates Perlin noise, which is a type of gradient noise used 
// in computer graphics for procedural texture generation. It produces a more natural 
// ordered appearance compared to the white noise functions.
class Perlin {
public:
    Perlin();
    ~Perlin();
    double noise(const ngl::Vec4& p) const;

private:
    static const int m_pointCount = 256;
    double* m_ranfloat;       // Pointer to an array of random float values
    int* m_permX;             // Permutation array for the x-coordinates
    int* m_permY;             // Permutation array for the y-coordinates
    int* m_permZ;             // Permutation array for the z-coordinates

    static int* perlinGeneratePerm();   // Generates a permutation array
    static void permute(int* p, int n); // Permutes/shuffles the provided array
    double trilinearInterp(double c[2][2][2], double u, double v, double w) const; // Trilinear interpolation function for smoothing values

};

#endif
