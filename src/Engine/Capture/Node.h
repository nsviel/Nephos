#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::k4n{class Node;}
namespace utl::element{class Profiler;}


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

  eng::k4n::Node* get_node_k4n(){return node_k4n;}

private:
  utl::element::Profiler* cpu_profiler;
  eng::k4n::Node* node_k4n;
};

}
