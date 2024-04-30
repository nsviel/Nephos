#pragma once

#include <Loader/src/Base/Importer.h>
#include <Utility/Specific/Common.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace format::xyz{

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  utl::File* import(utl::Path path);

private:
};

}
