#pragma once

#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Data/Namespace.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <GUI/TAB_render/Engine/Namespace.h>
#include <GUI/TAB_render/Kinect/Namespace.h>

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
  inline gui::engine::Shader* get_rnd_shader(){return rnd_shader;}
  inline gui::engine::Profiler* get_rnd_profiler(){return rnd_profiler;}
  inline gui::engine::Camera* get_rnd_camera(){return rnd_camera;}
  inline gui::engine::Render* get_rnd_render(){return rnd_render;}
  inline gui::rnd::panel::Scene* get_rnd_scene(){return rnd_scene;}
  inline gui::rnd::tab::Option* get_rnd_option(){return rnd_option;}

private:
  GUI* gui;
  gui::rnd::tab::Panel* gui_render_panel;
  gui::rnd::tab::Option* rnd_option;
  gui::rnd::tab::Menu* rnd_menu;
  gui::engine::Shader* rnd_shader;
  gui::engine::Profiler* rnd_profiler;
  gui::rnd::panel::Scene* rnd_scene;
  gui::engine::Render* rnd_render;
  gui::engine::Camera* rnd_camera;
  gui::kinect::Capture* rnd_capture;
  gui::kinect::Panel* rnd_kinect;
};

}
