#pragma once

#include <Utility/Specific/Common.h>

namespace app{class Node;}
namespace prf{class Node;}
namespace utl::element{class Window;}


namespace utl{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:


  inline prf::Node* get_node_profiler(){return node_profiler;}

private:
  prf::Node* node_profiler;
  utl::element::Window* utl_window;
};

}
