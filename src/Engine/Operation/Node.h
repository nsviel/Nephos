#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}


namespace eng::ope{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* engine);
  ~Node();

public:
  void init();
  void loop();
  void gui();
  void reset();

private:
  bool show_profiler;
};

}
