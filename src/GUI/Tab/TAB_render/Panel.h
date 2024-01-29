#pragma once

#include <Utility/Specific/common.h>

namespace eng::scene::gui{class Scene;}
namespace eng::scene::gui{class Loader;}
namespace gui{class Node;}
namespace gui::rnd::tab{class Option;}
namespace gui::rnd::tab{class Menu;}


namespace gui::rnd::tab{

class Panel
{
public:
  //Constructor / Destructor
  Panel(gui::Node* gui);
  ~Panel();

public:
  //Main functions
  void init_tab();
  void draw_tab();
  void open_panels();

  bool show_camera   = false;
  bool show_shader   = false;
  bool show_kinect   = true;
  bool show_profiler = true;
  bool show_scene    = true;
  bool show_option   = false;
  bool show_loader   = true;

private:
  gui::Node* gui;
  gui::rnd::tab::Option* rnd_option;
  gui::rnd::tab::Menu* rnd_menu;
};

}
