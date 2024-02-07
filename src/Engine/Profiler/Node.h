#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace profiler::gui{class Panel;}


namespace profiler{

class Node : public utl::type::Node
{
public:
  Node(eng::Node* engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline eng::Node* get_node_engine(){return engine;}

private:
  eng::Node* engine;
  profiler::gui::Panel* gui_panel;
};

}
