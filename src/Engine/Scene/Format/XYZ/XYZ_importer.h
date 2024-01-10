#pragma once

#include <Engine/Base/Namespace.h>
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
  eng::data::File* Loader(std::string filePath);

private:
  //Datatypes
  eng::data::File* data_out;
};
