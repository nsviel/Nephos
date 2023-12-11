#pragma once

#include <UTL_specific/common.h>
#include <TAB_render/Panel_nsp.h>
#include <TAB_render/Tab_nsp.h>
#include <TAB_render/Engine/Namespace.h>

class GUI;

namespace gui::rnd::tab{
class Menu;


class Tab
{
public:
  //Constructor / Destructor
  Tab(GUI* gui);
  ~Tab();

public:
  //Main functions
  void create_panels();
  void draw_panels();
  void open_panels();

  inline gui::rnd::tab::Panel* get_rnd_panel(){return gui_render_panel;}
  inline gui::rnd::engine::Shader* get_rnd_shader(){return rnd_shader;}
  inline gui::rnd::engine::Profiler* get_rnd_profiler(){return rnd_profiler;}
  inline gui::rnd::panel::Object* get_rnd_object(){return rnd_object;}
  inline gui::rnd::panel::Set* get_rnd_set(){return rnd_set;}
  inline gui::rnd::engine::Camera* get_rnd_camera(){return rnd_camera;}
  inline gui::rnd::engine::Render* get_rnd_render(){return rnd_render;}
  inline gui::rnd::panel::Scene* get_rnd_scene(){return rnd_scene;}
  inline gui::rnd::tab::Option* get_rnd_option(){return rnd_option;}

private:
  GUI* gui;
  gui::rnd::tab::Panel* gui_render_panel;
  gui::rnd::tab::Option* rnd_option;
  gui::rnd::tab::Menu* rnd_menu;
  gui::rnd::engine::Shader* rnd_shader;
  gui::rnd::engine::Profiler* rnd_profiler;
  gui::rnd::panel::Scene* rnd_scene;
  gui::rnd::engine::Render* rnd_render;
  gui::rnd::panel::Object* rnd_object;
  gui::rnd::engine::Camera* rnd_camera;
  gui::rnd::panel::Capture* rnd_capture;
  gui::rnd::panel::Kinect_panel* rnd_kinect;
  gui::rnd::panel::Set* rnd_set;
};

}
