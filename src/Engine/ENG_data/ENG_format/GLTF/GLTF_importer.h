#ifndef PTS_IMPORTER_H
#define PTS_IMPORTER_H

#include <UTL_base/Struct_file.h>
#include <UTL_base/Struct_object.h>
#include <UTL_file/Info.h>
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
  data::File* Loader(std::string pathFile);

  //Subfunction
  void load_file(std::string path);

private:
  tinygltf::Model model;
};

#endif
