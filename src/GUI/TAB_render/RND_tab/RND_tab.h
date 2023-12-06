#pragma once

#include <UTL_specific/common.h>

class GUI;
class RND_panel;

class RND_profiler;
class RND_shader;
class RND_engine;
class RND_option;
class RND_camera;
class RND_object;
class RND_set;
class RND_scene;
class RND_menu;
class RND_kinect;
class RND_capture;


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

  inline RND_panel* get_rnd_panel(){return gui_render_panel;}
  inline RND_shader* get_rnd_shader(){return rnd_shader;}
  inline RND_profiler* get_rnd_profiler(){return rnd_profiler;}
  inline RND_object* get_rnd_object(){return rnd_object;}
  inline RND_set* get_rnd_set(){return rnd_set;}
  inline RND_camera* get_rnd_camera(){return rnd_camera;}
  inline RND_engine* get_rnd_engine(){return rnd_engine;}
  inline RND_scene* get_rnd_scene(){return rnd_scene;}
  inline RND_option* get_rnd_option(){return rnd_option;}

private:
  GUI* gui;
  RND_panel* gui_render_panel;
  RND_option* rnd_option;
  RND_menu* rnd_menu;

  RND_profiler* rnd_profiler;
  RND_scene* rnd_scene;
  RND_shader* rnd_shader;
  RND_engine* rnd_engine;
  RND_object* rnd_object;
  RND_camera* rnd_camera;
  RND_capture* rnd_capture;
  RND_kinect* rnd_kinect;
  RND_set* rnd_set;
};
