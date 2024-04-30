#pragma once

#include <Loader/src/Base/Importer.h>
#include <Utility/Specific/Common.h>


namespace format::csv{

class Importer : public ldr::base::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  utl::type::File* import(std::string pathFile);

private:
};

}
