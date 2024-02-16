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
  //Main function
  utl::media::File* Loader(std::string filePath);

private:
  utl::media::File* data_out;
  std::string format;
};

}
