#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace sce{class Node;}
namespace ldr{class Loader;}
namespace utl::type{class Selection;}


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

private:
  eng::Node* node_engine;
  ldr::Loader* ldr_loader;
  utl::type::Selection* selection = nullptr;
};

}
