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
  void gui();

  //Subfunction
  void draw_menu();

private:
  //Dependancy
  eng::Node* node_engine;

  //Child
  eng::gui::Option* gui_option;
};

}
