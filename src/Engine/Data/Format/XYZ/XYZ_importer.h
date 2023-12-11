#pragma once

#include <Utility/Base/Struct_file.h>
#include <Utility/Function/File/Info.h>
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
  utility::base::File* Loader(std::string filePath);

private:
  //Datatypes
  utility::base::File* data_out;
};
