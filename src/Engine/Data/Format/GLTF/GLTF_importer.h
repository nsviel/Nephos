#pragma once

#include <Utility/Base/Struct_file.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Function/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <gltf/tiny_gltf.h>


class GLTF_importer
{
public:
  //Constructor / Destructor
  GLTF_importer();
  ~GLTF_importer();

public:
  //Main functions
  util::base::File* Loader(std::string pathFile);

  //Subfunction
  void load_file(std::string path);

private:
  tinygltf::Model model;
};
