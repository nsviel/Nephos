#pragma once

#include <Utility/Base/Namespace.h>
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
  utl::base::File* Loader(std::string filePath);

private:
  //Datatypes
  utl::base::File* data_out;
};
