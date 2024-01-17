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
  utl::media::File* Loader(std::string pathFile);

private:
  //Datatypes
  utl::media::File* data_out;
};
