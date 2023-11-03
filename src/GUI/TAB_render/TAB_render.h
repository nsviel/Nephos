
#ifndef GUI_RENDER_H
#define GUI_RENDER_H

#include <Specific/common.h>

class GUI;
class RND_panel;

class GUI_profiler;
class RND_shader;
class RND_engine;
class RND_option;
class GUI_database;
class PAN_camera;
class PAN_object;
class PAN_set;
class PAN_scene;
class GUI_capture;
class RND_menu;


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
  inline PAN_object* get_gui_object(){return gui_object;}
  inline PAN_set* get_gui_set(){return gui_set;}
  inline PAN_camera* get_gui_camera(){return gui_camera;}
  inline GUI_capture* get_gui_capture(){return gui_capture;}
  inline PAN_scene* get_gui_scene(){return gui_scene;}
  inline RND_engine* get_gui_engine(){return gui_engine;}
  inline RND_option* get_gui_option(){return gui_render_option;}

private:
  GUI* gui;
  RND_panel* gui_render_panel;
  RND_option* gui_render_option;
  RND_menu* gui_render_menu;

  GUI_profiler* gui_profiler;
  PAN_scene* gui_scene;
  RND_shader* gui_shader;
  RND_engine* gui_engine;
  GUI_database* gui_database;
  PAN_object* gui_object;
  PAN_camera* gui_camera;
  GUI_capture* gui_capture;
  PAN_set* gui_set;
};

#endif
