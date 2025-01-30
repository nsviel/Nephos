#pragma once

#include <IO/Base/Importer.h>
#include <gltf/tiny_gltf.h>
#include <memory>
#include <string>

namespace utl::base{class Path;}
namespace utl::base{class Data;}
namespace fmt::gltf::structure{class Model;}


namespace fmt::gltf{

class Importer : public io::base::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  void parse_mesh(tinygltf::Mesh& mesh);

  //Subfunction
  void parse_primitive_xyz(tinygltf::Primitive& primitive);
  void parse_primitive_xyz(tinygltf::Primitive& primitive);
  void parse_primitive_xyz(tinygltf::Primitive& primitive);
  void parse_primitive_xyz(tinygltf::Primitive& primitive);
  void parse_primitive_mode(tinygltf::Primitive& primitive);

private:
  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec3> vec_rgb;
};

}
