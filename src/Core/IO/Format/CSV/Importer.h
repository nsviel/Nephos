#pragma once

#include <Importer/src/Structure/Base.h>


namespace fmt::csv{

class Importer : public io::imp::Base
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