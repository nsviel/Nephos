#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::ope::gui{class Control;}
namespace eng::render::gui{class Profiler;}


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

  inline eng::ope::gui::Control* get_ope_control(){return ope_control;}

private:
  eng::ope::gui::Control* ope_control;
  eng::render::gui::Profiler* gui_profiler;
};

}
