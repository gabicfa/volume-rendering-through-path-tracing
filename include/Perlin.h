#ifndef PERLIN_H
#define PERLIN_H
#include "Utility.h"
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
        int* permZ;

        static int* perlinGeneratePerm();
        static void permute(int* p, int n);
};

#endif