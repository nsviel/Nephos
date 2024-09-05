#pragma once

#include <Importer/src/Base/Importer.h>


namespace fmt::csv{

class Importer : public io::base::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  std::shared_ptr<utl::base::Element> import(std::string pathFile);

private:
};

}
