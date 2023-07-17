#ifndef OBJFILE_H_
#define OBJFILE_H_
#include <string_view>
#include "Group.h"
#include "Triangle.h"

class ObjFile
{
    public:
        ObjFile();
        ObjFile(std::string_view _fname);
        void parseObjFile(std::string_view _fname);
        std::shared_ptr<Group> defaultGroup() const;
        void setDefaultGroup(std::shared_ptr<Group> _defaultGroup);
        std::vector<ngl::Vec3> vertices() const;
        std::vector<Triangle> fanTriangulation(std::vector<ngl::Vec3> _vertices);
        std::vector<std::shared_ptr<Triangle>> sceneObjects();
    private:
        std::shared_ptr<Group> m_defaultGroup;
        std::vector<ngl::Vec3> m_vertices;
        std::vector<std::shared_ptr<Triangle>> m_objects;

};

#endif
