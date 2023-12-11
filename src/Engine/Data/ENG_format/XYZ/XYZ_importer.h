#pragma once

#include <Utility/UTL_base/Struct_file.h>
#include <Utility/UTL_file/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


class XYZ_importer
{
public:
  //Constructor / Destructor
  XYZ_importer();
  ~XYZ_importer();

public:
  data::File* Loader(std::string filePath);

private:
  //Datatypes
  data::File* data_out;
};
