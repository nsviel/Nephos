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
  util::base::File* Loader(std::string filePath);

private:
  //Datatypes
  util::base::File* data_out;
};
