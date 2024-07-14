#pragma once

#include <Utility/Base/Class/Node.h>

namespace eng{class Node;}


namespace ope{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  //Subfunction

private:
  eng::Node* node_engine;
};

}
