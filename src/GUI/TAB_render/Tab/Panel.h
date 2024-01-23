#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Data/gui/Namespace.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <Engine/Camera/gui/Panel.h>
#include <Engine/Operation/gui/Profiler.h>
#include <GUI/TAB_render/Engine/Namespace.h>



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

  inline gui::engine::Shader* get_rnd_shader(){return rnd_shader;}
  inline gui::engine::Profiler* get_rnd_profiler(){return rnd_profiler;}
  inline camera::gui::Panel* get_cam_panel(){return cam_panel;}
  inline gui::engine::Renderer* get_rnd_render(){return rnd_render;}
  inline gui::rnd::data::Scene* get_rnd_scene(){return rnd_scene;}
  inline gui::rnd::tab::Option* get_rnd_option(){return rnd_option;}

private:
  GUI* gui;
  gui::rnd::tab::Option* rnd_option;
  gui::rnd::tab::Menu* rnd_menu;
  gui::engine::Shader* rnd_shader;
  gui::engine::Profiler* rnd_profiler;
  gui::engine::Renderer* rnd_render;
  camera::gui::Panel* cam_panel;

  gui::rnd::data::Scene* rnd_scene;
  gui::rnd::data::Loader* rnd_loader;
};

}
