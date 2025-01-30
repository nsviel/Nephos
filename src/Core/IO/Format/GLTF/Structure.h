#pragma once

#include <gltf/tiny_gltf.h>
#include <vector>


namespace fmt::gltf::structure{

struct Node{
  //---------------------------

  tinygltf::Node handle;
  std::vector<tinygltf::Mesh> vec_mesh;

  //---------------------------
};

struct Scene{
  //---------------------------

  tinygltf::Scene handle;
  std::vector<fmt::gltf::structure::Node> vec_node;

  //---------------------------
};

struct Model{
  //---------------------------

  tinygltf::Model handle;
  std::vector<fmt::gltf::structure::Scene> vec_scene;

  //---------------------------
};

}
