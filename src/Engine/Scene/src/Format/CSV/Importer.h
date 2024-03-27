#pragma once

#include <Utility/Specific/Common.h>


namespace format::csv{

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  utl::file::Entity* import(std::string pathFile);

private:
};

}
