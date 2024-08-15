#pragma once

#include <Importer/src/Structure/Base.h>
#include <Utility/Function/File/Path.h>
#include <gltf/tiny_gltf.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>


namespace fmt::gltf{

class Importer : public io::imp::Base
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  utl::base::Element* import(utl::base::Path path);

  //Subfunction
  void load_file(std::string path);

private:
  tinygltf::Model model;
};

}