#pragma once

#include <Utility/Specific/common.h>


namespace format::csv{

class Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  utl::media::File* import_data(std::string pathFile);

private:
  //Datatypes
  utl::media::File* data_out;
  std::string format;
};

}
