#include "BVHNode.h"
#include "Utility.h"
#include "AABB.h"

BVHNode::BVHNode() 
{
}

BVHNode::BVHNode(const Group& list, double time0, double time1) 
{
}

bool BVHNode::operator==(const Shape& _other) const
{
    if (const BVHNode* bvhNode = dynamic_cast<const BVHNode*>(&_other))
        {
            return (m_left == bvhNode->m_left &&
                    m_right == bvhNode->m_right &&
                    m_box == bvhNode->m_box);
        }
        return false;
}

bool BVHNode::operator!=(const Shape& _other) const
{
    if (const BVHNode* bvhNode = dynamic_cast<const BVHNode*>(&_other))
    {
        return (m_left != bvhNode->m_left ||
                m_right != bvhNode->m_right ||
                m_box != bvhNode->m_box);
    }
    return true;
}


ngl::Vec4 BVHNode::localNormalAt(ngl::Vec4 _localPoint)
{
    // This method might not make sense for a BVHNode as it's a 
    // hierarchical data structure for organizing shapes, not a shape itself.
    // Therefore, it does not have a "surface" where a normal vector can be calculated.
    // Typically, you would instead ask one of the child nodes for their normal at a given point.
    throw std::logic_error("Cannot calculate local normal of a BVHNode");
}

bool boxCompare(const std::shared_ptr<Shape>& a, const std::shared_ptr<Shape>& b, int axis) {
    AABB boxA, boxB;

    if (!a->boundingBox(0, 0, boxA) || !b->boundingBox(0, 0, boxB))
        std::cerr << "No bounding m_box in BVHNode constructor.\n";

    return boxA.min()[axis] < boxB.min()[axis];
}

bool boxXCompare(const std::shared_ptr<Shape>& a, const std::shared_ptr<Shape>& b) { return boxCompare(a, b, 0); }
bool boxYCompare(const std::shared_ptr<Shape>& a, const std::shared_ptr<Shape>& b) { return boxCompare(a, b, 1); }
bool boxZCompare(const std::shared_ptr<Shape>& a, const std::shared_ptr<Shape>& b) { return boxCompare(a, b, 2); }

BVHNode::BVHNode(const std::vector<std::shared_ptr<Shape>>& src_objects, size_t start, size_t end, double time0, double time1) {
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = randomInt(0,2);
    auto comparator = (axis == 0) ? boxXCompare
                    : (axis == 1) ? boxYCompare
                                  : boxZCompare;

    size_t object_span = end - start;

    if (object_span == 1) {
        m_left = m_right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            m_left = objects[start];
            m_right = objects[start+1];
        } else {
            m_left = objects[start+1];
            m_right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        m_left = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
        m_right = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB box_left, box_right;

    if (  !m_left->boundingBox(0, 0, box_left)
       || !m_right->boundingBox(0, 0, box_right)
    )
        std::cerr << "No bounding m_box in BVHNode constructor.\n";

    m_box = AABB::surroundingBox(box_left, box_right);
}

std::vector<Intersection> BVHNode::localIntersect(Ray _r) {
    std::vector<Intersection> intersections;
    if (m_box.intersect(_r, 0, std::numeric_limits<double>::max())) 
    {

        auto leftIntersections = m_left->localIntersect(_r);
        auto rightIntersections = m_right->localIntersect(_r);

        intersections.insert(intersections.end(), leftIntersections.begin(), leftIntersections.end());
        intersections.insert(intersections.end(), rightIntersections.begin(), rightIntersections.end());

    }
    return intersections;
}


bool BVHNode::boundingBox(double time0, double time1, AABB& outputm_box) const 
{
    outputm_box = m_box;
    return true;
}
