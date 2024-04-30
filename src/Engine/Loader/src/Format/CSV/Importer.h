#pragma once

#include <Loader/src/Base/Importer.h>


namespace format::csv{

class Importer : public ldr::base::Importer
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
