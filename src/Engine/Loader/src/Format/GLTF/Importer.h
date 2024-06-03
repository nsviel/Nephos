#pragma once

#include <Loader/src/Base/Importer.h>
#include <Utility/Function/File/Path.h>
#include <gltf/tiny_gltf.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>


namespace format::gltf{

class Importer : public ldr::base::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main functions
  utl::base::Element* import(utl::base::Path path);

  //Subfunction
  void load_file(std::string path);

private:
  tinygltf::Model model;
};

}
