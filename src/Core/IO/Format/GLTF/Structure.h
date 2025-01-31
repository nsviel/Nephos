#pragma once

#include <Utility/Base/Data/Path.h>
#include <glm/glm.hpp>
#include <vector>


namespace fmt::gltf{

struct Structure{
  //---------------------------

  tinygltf::Model model;
  tinygltf::Mesh mesh;
  tinygltf::Primitive primitive;

  //---------------------------
};

}
