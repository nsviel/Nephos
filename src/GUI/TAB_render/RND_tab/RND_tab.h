#pragma once

#include <UTL_specific/common.h>
#include <TAB_render/Panel_nsp.h>
#include <TAB_render/Tab_nsp.h>

class GUI;

namespace gui::rnd::tab{
class RND_menu;


class RND_tab
{
public:
  //Constructor / Destructor
  RND_tab(GUI* gui);
  ~RND_tab();

public:
  //Main functions
  void create_panels();
  void draw_panels();
  void open_panels();

  inline gui::rnd::tab::RND_panel* get_rnd_panel(){return gui_render_panel;}
  inline gui::rnd::panel::Shader* get_rnd_shader(){return rnd_shader;}
  inline gui::rnd::panel::Profiler* get_rnd_profiler(){return rnd_profiler;}
  inline gui::rnd::panel::Object* get_rnd_object(){return rnd_object;}
  inline gui::rnd::panel::Set* get_rnd_set(){return rnd_set;}
  inline gui::rnd::panel::Camera* get_rnd_camera(){return rnd_camera;}
  inline gui::rnd::panel::Render* get_rnd_render(){return rnd_render;}
  inline gui::rnd::panel::Scene* get_rnd_scene(){return rnd_scene;}
  inline gui::rnd::tab::RND_option* get_rnd_option(){return rnd_option;}

private:
  GUI* gui;
  gui::rnd::tab::RND_panel* gui_render_panel;
  gui::rnd::tab::RND_option* rnd_option;
  gui::rnd::tab::RND_menu* rnd_menu;
  gui::rnd::panel::Shader* rnd_shader;
  gui::rnd::panel::Profiler* rnd_profiler;
  gui::rnd::panel::Scene* rnd_scene;
  gui::rnd::panel::Render* rnd_render;
  gui::rnd::panel::Object* rnd_object;
  gui::rnd::panel::Camera* rnd_camera;
  gui::rnd::panel::Capture* rnd_capture;
  gui::rnd::panel::Kinect_panel* rnd_kinect;
  gui::rnd::panel::Set* rnd_set;
};

}
