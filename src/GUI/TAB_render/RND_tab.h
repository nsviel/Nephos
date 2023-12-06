#ifndef TAB_RENDER_H
#define TAB_RENDER_H

#include <UTL_specific/common.h>

class GUI;
class RND_panel;

class GUI_profiler;
class RND_shader;
class RND_engine;
class RND_option;
class RND_camera;
class RND_object;
class RND_set;
class RND_scene;
class RND_menu;
class GUI_kinect;
class KIN_capture;


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

  inline RND_panel* get_render_panel(){return gui_render_panel;}
  inline RND_shader* get_gui_shader(){return gui_shader;}
  inline GUI_profiler* get_gui_profiling(){return gui_profiler;}
  inline RND_object* get_rnd_object(){return rnd_object;}
  inline RND_set* get_rnd_set(){return rnd_set;}
  inline RND_camera* get_gui_camera(){return gui_stream;}
  inline RND_engine* get_gui_engine(){return gui_engine;}
  inline RND_scene* get_gui_scene(){return gui_scene;}
  inline RND_option* get_gui_option(){return rnd_option;}

private:
  GUI* gui;
  RND_panel* gui_render_panel;
  RND_option* rnd_option;
  RND_menu* rnd_menu;

  GUI_profiler* gui_profiler;
  RND_scene* gui_scene;
  RND_shader* gui_shader;
  RND_engine* gui_engine;
  RND_object* rnd_object;
  RND_camera* gui_stream;
  KIN_capture* gui_capture;
  GUI_kinect* gui_kinect;
  RND_set* rnd_set;
};

#endif
