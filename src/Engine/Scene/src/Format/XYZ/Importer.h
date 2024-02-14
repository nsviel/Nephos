#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace format::xyz{

class Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  utl::media::File* Loader(std::string filePath);

private:
  //Datatypes
  utl::media::File* data_out;
};

}
