#pragma once

#include <IO/Base/Importer.h>
#include <Utility/Function/File/Path.h>
#include <string>


namespace fmt::gltf{

class Importer : public io::base::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  std::shared_ptr<utl::base::Element> import(utl::base::Path path);

  //Subfunction
  void load_file(std::string path);

private:

};

}
