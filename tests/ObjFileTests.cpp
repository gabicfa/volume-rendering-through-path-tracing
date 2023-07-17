#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <ngl/Obj.h>
#include <memory>
#include "ObjFile.h"
#include "Triangle.h"

TEST(Obj,checkVerts)
{
  ObjFile obj("files/Triangle1.obj");
  ASSERT_EQ(obj.vertices()[0], ngl::Vec3(2.00000f, 0.00000f, 0.000000f));
  ASSERT_EQ(obj.vertices()[1], ngl::Vec3(0.0000f, 4.0000f, 0.000000f));
  ASSERT_EQ(obj.vertices()[2], ngl::Vec3(-2.00000f, 0.000000f, 0.000000f));
}

TEST(Obj, ParsingTriangleFaces)
{
  ObjFile obj("files/Triangle2.obj");
  auto g = obj.defaultGroup();
  auto t1 = std::dynamic_pointer_cast<Triangle>(g->getChildren()[0]);
  auto t2 = std::dynamic_pointer_cast<Triangle>(g->getChildren()[1]);
  ASSERT_EQ(t1->getP1(), obj.vertices()[0]);
  ASSERT_EQ(t1->getP2(), obj.vertices()[1]);
  ASSERT_EQ(t1->getP3(), obj.vertices()[2]);
  ASSERT_EQ(t2->getP1(), obj.vertices()[0]);
  ASSERT_EQ(t2->getP2(), obj.vertices()[2]);
  ASSERT_EQ(t2->getP3(), obj.vertices()[3]);
}

TEST(Obj, ParsingPentagonalFace)
{
  ObjFile obj("files/Pentagon1.obj");
  auto g = obj.defaultGroup();
  auto t1 = std::dynamic_pointer_cast<Triangle>(g->getChildren()[0]);
  auto t2 = std::dynamic_pointer_cast<Triangle>(g->getChildren()[1]);
  auto t3 = std::dynamic_pointer_cast<Triangle>(g->getChildren()[2]);
  ASSERT_EQ(t1->getP1(), obj.vertices()[0]);
  ASSERT_EQ(t1->getP2(), obj.vertices()[1]);
  ASSERT_EQ(t1->getP3(), obj.vertices()[2]);
  ASSERT_EQ(t2->getP1(), obj.vertices()[0]);
  ASSERT_EQ(t2->getP2(), obj.vertices()[2]);
  ASSERT_EQ(t2->getP3(), obj.vertices()[3]);
  ASSERT_EQ(t3->getP1(), obj.vertices()[0]);
  ASSERT_EQ(t3->getP2(), obj.vertices()[3]);
  ASSERT_EQ(t3->getP3(), obj.vertices()[4]);
}

TEST(Obj, TriangleInGroups)
{
  ObjFile obj("files/Triangle3.obj");
  auto g = obj.defaultGroup();
  auto t1 = std::dynamic_pointer_cast<Triangle>(g->getChildren()[0]);
  auto t2 = std::dynamic_pointer_cast<Triangle>(g->getChildren()[1]);
  auto t3 = std::dynamic_pointer_cast<Triangle>(g->getChildren()[2]);
  ASSERT_EQ(t1->getP1(), obj.vertices()[0]);
  ASSERT_EQ(t1->getP2(), obj.vertices()[1]);
  ASSERT_EQ(t1->getP3(), obj.vertices()[2]);
  ASSERT_EQ(t2->getP1(), obj.vertices()[0]);
  ASSERT_EQ(t2->getP2(), obj.vertices()[2]);
  ASSERT_EQ(t2->getP3(), obj.vertices()[3]);
  ASSERT_EQ(t3->getP1(), obj.vertices()[0]);
  ASSERT_EQ(t3->getP2(), obj.vertices()[3]);
  ASSERT_EQ(t3->getP3(), obj.vertices()[4]);
}


