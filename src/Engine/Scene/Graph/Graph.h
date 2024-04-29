#pragma once

#include <Utility/Specific/Common.h>

namespace sce{class Node;}
namespace ldr{class Loader;}
namespace utl::type{class Selection;}


namespace sce{

class Graph
{
public:
  //Constructor / Destructor
  Graph(sce::Node* node_scene);
  ~Graph();

public:
  //Main function
  void init();

private:
  ldr::Loader* ldr_loader;
  utl::type::Selection* selection = nullptr;
};

}
