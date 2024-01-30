#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::k4n{class Node;}


namespace eng::capture{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();

private:
  eng::k4n::Node* k4n_node;
};

}
