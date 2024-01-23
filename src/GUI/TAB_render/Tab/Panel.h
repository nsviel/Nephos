#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Data/gui/Namespace.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <Engine/Camera/gui/Panel.h>
#include <Engine/Operation/gui/Namespace.h>
#include <Engine/Render/gui/Namespace.h>



class GUI;

namespace gui::rnd::tab{
class Menu;


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

  inline eng::render::gui::Shader* get_rnd_shader(){return rnd_shader;}
  inline ope::gui::Profiler* get_rnd_profiler(){return rnd_profiler;}
  inline camera::gui::Panel* get_cam_panel(){return cam_panel;}
  inline eng::render::gui::Renderer* get_rnd_render(){return rnd_render;}
  inline gui::rnd::data::Scene* get_rnd_scene(){return rnd_scene;}
  inline gui::rnd::tab::Option* get_rnd_option(){return rnd_option;}

private:
  GUI* gui;
  gui::rnd::tab::Option* rnd_option;
  gui::rnd::tab::Menu* rnd_menu;
  eng::render::gui::Shader* rnd_shader;
  ope::gui::Profiler* rnd_profiler;
  eng::render::gui::Renderer* rnd_render;
  camera::gui::Panel* cam_panel;

  gui::rnd::data::Scene* rnd_scene;
  gui::rnd::data::Loader* rnd_loader;
};

}
