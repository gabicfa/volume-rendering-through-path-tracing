#include "Computation.h"
#include "Shape.h"
#include "Material.h"
#include "Ray.h"

void Computation::recompute()
{
    // Recalculate the normal at the intersection point.
    normal = object->normalAt(point);

    // Check if the intersection is inside the object based on the direction of the incoming ray.
    inside = incomingRay.direction().dot(normal) < 0.0f;

    // If inside, flip the normal vector to point outside.
    if (inside)
    {
        this->normal = -this->normal;
    }

    // Calculate the eye vector direction.
    this->eye = -incomingRay.direction();
}