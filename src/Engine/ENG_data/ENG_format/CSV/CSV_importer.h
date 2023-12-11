#pragma once

#include <UTL_base/Struct_file.h>
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
  data::File* Loader(std::string pathFile);

private:
  //Datatypes
  data::File* data_out;
};
