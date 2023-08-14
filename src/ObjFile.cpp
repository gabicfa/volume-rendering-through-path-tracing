#include "ObjFile.h"
#include <ngl/Obj.h>
#include "Triangle.h"


// Default constructor initializes default group.
ObjFile::ObjFile()
    : m_defaultGroup(std::make_shared<Group>())
{
}

// Constructor that initializes with default group and then parses the given .obj file.
ObjFile::ObjFile(std::string_view _fname)
    : ObjFile()
{
    parseObjFile(_fname);
}

// Parse the given .obj file and extract its geometric information.
void ObjFile::parseObjFile(std::string_view _fname)
{
    ngl::Obj obj;
    obj.load(_fname);
    m_vertices = obj.getVertexList();
    const auto& faceList = obj.getFaceList();

    // Iterate through faces and process them.
    // Triangulate if the face has more than 3 vertices.
    std::for_each(faceList.begin(), faceList.end(), [this](const ngl::Face& face) {
        if (face.m_vert.size() > 3)
        {
            std::vector<ngl::Vec3> vertices;
            std::transform(face.m_vert.begin(), face.m_vert.end(), std::back_inserter(vertices), [this](size_t index) {
                return m_vertices[index];
            });

            const auto triangles = fanTriangulation(vertices);
            std::for_each(triangles.begin(), triangles.end(), [this](const Triangle& t) {
                m_defaultGroup->addChild(std::make_shared<Triangle>(t));
            });
        }
        else
        {
            const auto t = Triangle(m_vertices[face.m_vert[0]], m_vertices[face.m_vert[1]], m_vertices[face.m_vert[2]]);
            m_defaultGroup->addChild(std::make_shared<Triangle>(t));
        }
    });
}

// Convert a polygon with more than 3 vertices into triangles.
std::vector<Triangle> ObjFile::fanTriangulation(std::vector<ngl::Vec3> _vertices)
{
    std::vector<Triangle> triangles;
    for (size_t index = 1; index < _vertices.size() - 1; ++index)
    {
        Triangle tri(_vertices[0], _vertices[index], _vertices[index + 1]);
        triangles.push_back(tri);
    }
    return triangles;
}

std::shared_ptr<Group> ObjFile::defaultGroup() const
{
    return m_defaultGroup;
}

void ObjFile::setDefaultGroup(std::shared_ptr<Group> _defaultGroup)
{
    m_defaultGroup = _defaultGroup;
}

std::vector<ngl::Vec3> ObjFile::vertices() const
{
    return m_vertices;
}
