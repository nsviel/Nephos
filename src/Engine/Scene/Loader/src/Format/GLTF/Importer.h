#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <gltf/tiny_gltf.h>


namespace format::gltf{

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main functions
  utl::File* import(utl::Path path);

  //Subfunction
  void load_file(std::string path);

private:
  tinygltf::Model model;
};

}