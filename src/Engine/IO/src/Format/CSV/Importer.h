#pragma once

#include <IO/src/Import/Structure/Base.h>


namespace fmt::csv{

class Importer : public ldr::importer::Base
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  utl::base::Element* import(std::string pathFile);

private:
};

}
