#include "Perlin.h"

Perlin::Perlin() {
    m_ranfloat = new double[m_pointCount];
    for (int i = 0; i < m_pointCount; ++i) {
        m_ranfloat[i] = randomDouble();
    }

    m_permX = perlinGeneratePerm();
    m_permY = perlinGeneratePerm();
    permZ = perlinGeneratePerm();
}

Perlin::~Perlin() {
    delete[] m_ranfloat;
    delete[] m_permX;
    delete[] m_permY;
    delete[] permZ;
}

double Perlin::noise(const ngl::Vec4& p) const {
    auto i = static_cast<int>(4*p.m_x) & 255;
    auto j = static_cast<int>(4*p.m_y) & 255;
    auto k = static_cast<int>(4*p.m_z) & 255;

    return m_ranfloat[m_permX[i] ^ m_permY[j] ^ permZ[k]];
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
