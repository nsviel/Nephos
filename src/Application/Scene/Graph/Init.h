#pragma once

namespace core{class Node;}
namespace sce{class Node;}
namespace io::imp{class Structure;}
namespace io::imp{class Loader;}
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
  core::Node* node_core;
  io::imp::Loader* io_loader;
  io::imp::Structure* io_struct;
  utl::base::Selection* selection = nullptr;
};

}
