#pragma once

#include <Utility/Specific/common.h>


namespace format::csv{

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  utl::media::File* import(std::string pathFile);

private:
};

}
