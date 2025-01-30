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
  std::shared_ptr<utl::base::Element> import(utl::base::Path path);

  //Subfunction
  void load_gltf(std::string path, tinygltf::Model& model);
  void load_glb(std::string path, tinygltf::Model& model);
  void info_model(tinygltf::Model& model);
  void parse_meshes(tinygltf::Model& model, std::shared_ptr<utl::base::Data> data);
  void parse_mode(int mode, std::shared_ptr<utl::base::Data> data);
  
private:

};

}
