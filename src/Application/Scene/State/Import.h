#pragma once

#include <Utility/Namespace.h>
#include <memory>

namespace sce{class Node;}
namespace sce{class Structure;}
namespace io::imp{class Structure;}
namespace io::imp{class Loader;}


namespace sce{

class Import
{
public:
  //Constructor / Destructor
  Import(sce::Node* node_scene);
  ~Import();

public:
  //Main function
  void init();
  void import_json();

  //Subfunction
  void load_objects(std::string path);

private:
  io::imp::Loader* io_loader;
  io::imp::Structure* io_struct;

  sce::Structure* sce_struct;
};

}
