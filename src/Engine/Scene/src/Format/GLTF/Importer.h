#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <gltf/tiny_gltf.h>


namespace format::gltf{

class Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main functions
  utl::media::File* import_data(std::string pathFile);

  //Subfunction
  void load_file(std::string path);

private:
  tinygltf::Model model;
  std::string format;
};

}
