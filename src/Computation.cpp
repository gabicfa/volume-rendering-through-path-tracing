#include "Computation.h"
#include "Shape.h"
#include "Material.h"
#include "Ray.h"
void Computation::recompute()
{
    normal = object->normalAt(point);
    inside = incomingRay.direction().dot(normal) < 0.0f;
    if (inside)
    {
        this->normal = -this->normal;
    }
    this->eye = -incomingRay.direction();
}