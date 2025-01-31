#pragma once

#include <gltf/tiny_gltf.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace fmt::gltf{class Structure;}
namespace utl::base{class Data;}
namespace utl::base{class Path;}


namespace fmt::gltf{

class Model
{
public:
  //Constructor / Destructor
  Model();
  ~Model();

public:
  //Main function
  void load_model(fmt::gltf::Structure& tinygltf, utl::base::Path path);
  void info_model(tinygltf::Model& model);

  //Subfunction
  void load_gltf(std::string path, tinygltf::Model& model);
  void load_glb(std::string path, tinygltf::Model& model);

private:
};

}
