#pragma once

#include <Engine/Base/Namespace.h>
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
  eng::data::File* Loader(std::string pathFile);

private:
  //Datatypes
  eng::data::File* data_out;
};
