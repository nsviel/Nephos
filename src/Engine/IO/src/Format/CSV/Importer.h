#pragma once

#include <IO/src/Import/Structure/Importer.h>


namespace fmt::csv{

class Importer : public ldr::base::Importer
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
