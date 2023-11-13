#ifndef XYZ_IMPORTER_H
#define XYZ_IMPORTER_H

#include <UTL_specific/Struct/struct_data_file.h>
#include <UTL_specific/File/Info.h>
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
  Data_file* Loader(std::string filePath);

private:
  //Datatypes
  Data_file* data_out;
};

#endif
