#pragma once

namespace eng{class Node;}
namespace sce{class Node;}
namespace io::imp{class Structure;}
namespace io::imp{class Importer;}
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
  io::imp::Importer* io_importer;
  io::imp::Structure* io_struct;
  utl::base::Selection* selection = nullptr;
};

}
