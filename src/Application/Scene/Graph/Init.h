#pragma once

namespace eng{class Node;}
namespace sce{class Node;}
namespace io{class Structure;}
namespace io{class Importer;}
namespace utl::base{class Selection;}


namespace sce{

class Init
{
public:
  //Constructor / Destructor
  Init(sce::Node* node_scene);
  ~Init();

public:
  //Main function
  void init();

  //Subfunction
  void load_entity();

private:
  eng::Node* node_engine;
  io::Importer* io_loader;
  io::Structure* io_struct;
  utl::base::Selection* selection = nullptr;
};

}
