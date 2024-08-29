#pragma once

#include <Utility/Base/Class/Node.h>

namespace sys{class Node;}


namespace thr{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(sys::Node* node_system);
  ~Node();

public:
  //Main function
  void init();

private:

};

}
