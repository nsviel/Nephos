#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::gui{class Option;}


namespace eng::gui{

class Tab
{
public:
  //Constructor / Destructor
  Tab(eng::Node* node_engine);
  ~Tab();

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
  eng::gui::Option* gui_option;
};

}
