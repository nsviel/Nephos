#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace prf{class Node;}


namespace sys{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();

  inline prf::Node* get_node_profiler(){return node_profiler;}

private:
  prf::Node* node_profiler;
};

}
