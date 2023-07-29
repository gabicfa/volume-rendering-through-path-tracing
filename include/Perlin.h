#ifndef PERLIN_H
#define PERLIN_H
#include <ngl/Vec3.h>

class Perlin {
    public:
        Perlin();
        ~Perlin();
        double noise(const ngl::Vec4& p) const;

    private:
        static const int m_pointCount = 256;
        double* m_ranfloat;
        int* m_permX;
        int* m_permY;
        int* m_permZ;

        static int* perlinGeneratePerm();
        static void permute(int* p, int n);
        double trilinearInterp(double c[2][2][2], double u, double v, double w) const;

};

#endif