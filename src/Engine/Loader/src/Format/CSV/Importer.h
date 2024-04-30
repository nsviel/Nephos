#pragma once

#include <Loader/src/Base/Importer.h>
#include <Utility/Specific/Common.h>


namespace format::csv{

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  utl::File* import(std::string pathFile);

private:
};

}
