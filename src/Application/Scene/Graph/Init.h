#pragma once

namespace eng{class Node;}
namespace sce{class Node;}
namespace ldr{class Importer;}
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
  ldr::Importer* ldr_loader;
  utl::base::Selection* selection = nullptr;
};

}
