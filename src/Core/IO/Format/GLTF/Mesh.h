#pragma once

#include <gltf/tiny_gltf.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace fmt::gltf{class Structure;}
namespace utl::base{class Data;}


namespace fmt::gltf{

class Mesh
{
public:
  //Constructor / Destructor
  Mesh();
  ~Mesh();

public:
  //Main function
  void parse_meshes(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data);
  void parse_mesh(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data);

  //Subfunction
  void parse_primitive_xyz(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data);
  void parse_primitive_rgb(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data);
  void parse_primitive_uv(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data);
  void parse_primitive_mode(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data);
  void parse_primitive_idx(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data);
  void parse_primitive_tex(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data);

private:
};

}
