#pragma once

#include <Utility/Base/Struct_file.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


class CSV_importer
{
public:
  //Constructor / Destructor
  CSV_importer();
  ~CSV_importer();

public:
  utility::base::File* Loader(std::string pathFile);

private:
  //Datatypes
  utility::base::File* data_out;
};
