#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::gui{class Option;}


namespace eng::gui{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main functions
  void init();
  void draw_tab();
  void open_panels();

  //Subfunction
  void draw_menu();

private:
  eng::Node* node_engine;
  eng::gui::Option* gui_option;
};

}
