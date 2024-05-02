#pragma once

#include <Utility/Base/Type/Node.h>

namespace eng{class Node;}


namespace dyn{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

private:

};

}
