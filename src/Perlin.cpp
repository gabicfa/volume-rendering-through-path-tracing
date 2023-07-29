#include "Perlin.h"
#include "Utility.h"

Perlin::Perlin() {
    m_ranfloat = new double[m_pointCount];
    for (int i = 0; i < m_pointCount; ++i) {
        m_ranfloat[i] = randomDouble(0.0, 1.0);
    }

    m_permX = perlinGeneratePerm();
    m_permY = perlinGeneratePerm();
    m_permZ = perlinGeneratePerm();
}

Perlin::~Perlin() {
    delete[] m_ranfloat;
    delete[] m_permX;
    delete[] m_permY;
    delete[] m_permZ;
}

double Perlin::noise(const ngl::Vec4& p) const {
    auto u = p.m_x - std::floor(p.m_x);
    auto v = p.m_y - std::floor(p.m_y);
    auto w = p.m_z - std::floor(p.m_z);
    
    u = u*u*(3-2*u);
    v = v*v*(3-2*v);
    w = w*w*(3-2*w);

    auto i = static_cast<int>(std::floor(p.m_x));
    auto j = static_cast<int>(std::floor(p.m_y));
    auto k = static_cast<int>(std::floor(p.m_z));

    double c[2][2][2];

    for (int di=0; di < 2; di++)
        for (int dj=0; dj < 2; dj++)
            for (int dk=0; dk < 2; dk++)
                c[di][dj][dk] = m_ranfloat[
                    m_permX[(i+di) & 255] ^
                    m_permY[(j+dj) & 255] ^
                    m_permZ[(k+dk) & 255]
                ];

    return trilinearInterp(c, u, v, w);
}

int* Perlin::perlinGeneratePerm() {
    auto p = new int[m_pointCount];

    for (int i = 0; i < Perlin::m_pointCount; i++)
        p[i] = i;

    permute(p, m_pointCount);

    return p;
}

void Perlin::permute(int* p, int n) {
    for (int i = n-1; i > 0; i--) {
        int target = randomInt(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

double Perlin::trilinearInterp(double c[2][2][2], double u, double v, double w) const {
    auto accum = 0.0;
    for (int i=0; i < 2; i++)
        for (int j=0; j < 2; j++)
            for (int k=0; k < 2; k++)
                accum += (i*u + (1-i)*(1-u))*
                        (j*v + (1-j)*(1-v))*
                        (k*w + (1-k)*(1-w))*c[i][j][k];

    return accum;
}

