#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::ope{class Wheel;}
namespace eng::ope::gui{class Control;}


namespace eng::ope{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void gui();
  void control();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline eng::ope::Wheel* get_ope_wheel(){return ope_wheel;}
  inline eng::ope::gui::Control* get_gui_control(){return gui_control;}

private:
  eng::Node* node_engine;
  eng::ope::Wheel* ope_wheel;
  eng::ope::gui::Control* gui_control;
};

}
