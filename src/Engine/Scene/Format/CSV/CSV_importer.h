#pragma once

#include <Utility/Base/Namespace.h>
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
  eng::base::File* Loader(std::string pathFile);

private:
  //Datatypes
  eng::base::File* data_out;
};
