#include "Computation.h"
#include "Shape.h"
#include "Material.h"
#include "Ray.h"
void Computation::recompute(const ngl::Vec4 &newPoint, ngl::Vec4 dir) 
{
    point = newPoint;
    eye = - dir;
    normal = object->normalAt(point);
    matPtr = object->material();

    if (normal.dot(eye) < 0)
    {
        inside = true;
        normal = -normal;
    }
    else
    {
        inside = false;
    }
}