#ifndef TAB_RENDER_H
#define TAB_RENDER_H

#include <UTL_specific/common.h>

class GUI;
class RND_panel;

class GUI_profiler;
class RND_shader;
class RND_engine;
class RND_option;
class GUI_database;
class RND_camera;
class RND_object;
class RND_set;
class RND_scene;
class GUI_camera;
class RND_menu;
class GUI_kinect;
class GUI_capture;


class TAB_render
{
public:
  //Constructor / Destructor
  TAB_render(GUI* gui);
  ~TAB_render();

public:
  //Main functions
  void create_panels();
  void draw_panels();
  void open_panels();

  inline RND_panel* get_render_panel(){return gui_render_panel;}
  inline RND_shader* get_gui_shader(){return gui_shader;}
  inline GUI_profiler* get_gui_profiling(){return gui_profiler;}
  inline RND_object* get_gui_object(){return gui_object;}
  inline RND_set* get_gui_set(){return gui_set;}
  inline RND_camera* get_gui_camera(){return gui_stream;}
  inline GUI_camera* get_gui_capture(){return gui_camera;}
  inline RND_engine* get_gui_engine(){return gui_engine;}
  inline RND_scene* get_gui_scene(){return gui_scene;}
  inline RND_option* get_gui_option(){return gui_render_option;}

private:
  GUI* gui;
  RND_panel* gui_render_panel;
  RND_option* gui_render_option;
  RND_menu* gui_render_menu;

  GUI_profiler* gui_profiler;
  RND_scene* gui_scene;
  RND_shader* gui_shader;
  RND_engine* gui_engine;
  GUI_database* gui_database;
  RND_object* gui_object;
  RND_camera* gui_stream;
  GUI_camera* gui_camera;
  GUI_capture* gui_capture;
  GUI_kinect* gui_kinect;
  RND_set* gui_set;
};

#endif
