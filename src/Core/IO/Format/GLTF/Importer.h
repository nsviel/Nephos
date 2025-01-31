#pragma once

#include <IO/Base/Importer.h>
#include <gltf/tiny_gltf.h>
#include <memory>
#include <string>

namespace utl::base{class Path;}
namespace utl::base{class Data;}
namespace fmt::gltf{class Mesh;}
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
  std::shared_ptr<utl::base::Element> import(utl::base::Path path);

  //Subfunction
  void load_gltf(std::string path, tinygltf::Model& model);
  void load_glb(std::string path, tinygltf::Model& model);
  void info_model(tinygltf::Model& model);

private:
  fmt::gltf::Mesh* gltf_mesh;
};

}
