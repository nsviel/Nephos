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
  void draw_tab();
  void open_panels();

  //Subfunction
  void draw_menu();

  bool show_camera   = false;
  bool show_shader   = false;
  bool show_kinect   = true;
  bool show_profiler = true;
  bool show_scene    = true;
  bool show_option   = false;
  bool show_loader   = true;

private:
  eng::Node* node_engine;
  eng::gui::Option* gui_option;
};

}
