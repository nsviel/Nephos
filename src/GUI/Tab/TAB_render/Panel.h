#pragma once

#include <GUI/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Render/gui/Namespace.h>

namespace eng::scene::gui{class Scene;}
namespace eng::scene::gui{class Loader;}
class GUI;
namespace gui::rnd::tab{class Menu;}


namespace gui::rnd::tab{

class Panel
{
public:
  //Constructor / Destructor
  Panel(GUI* gui);
  ~Panel();

public:
  //Main functions
  void create_panels();
  void draw_panels();
  void open_panels();

  bool show_camera   = false;
  bool show_shader   = false;
  bool show_kinect   = true;
  bool show_profiler = true;
  bool show_scene    = true;
  bool show_option   = false;
  bool show_loader   = true;

private:
  GUI* gui;
  gui::rnd::tab::Option* rnd_option;
  gui::rnd::tab::Menu* rnd_menu;
};

}
