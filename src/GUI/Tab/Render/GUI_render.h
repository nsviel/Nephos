#ifndef GUI_RENDER_H
#define GUI_RENDER_H

#include <Specific/common.h>

class GUI;
class GUI_render_panel;

class GUI_profiler;
class GUI_shader;
class GUI_engine;
class GUI_render_option;
class GUI_database;
class GUI_camera;
class GUI_object;
class GUI_set;
class GUI_scene;
class GUI_capture;
class GUI_render_menu;


class GUI_render
{
public:
  //Constructor / Destructor
  GUI_render(GUI* gui);
  ~GUI_render();

public:
  //Main functions
  void create_panels();
  void draw_panels();
  void open_panels();

  inline GUI_render_panel* get_panel(){return gui_render_panel;}
  inline GUI_shader* get_gui_shader(){return gui_shader;}
  inline GUI_profiler* get_gui_profiling(){return gui_profiler;}
  inline GUI_object* get_gui_object(){return gui_object;}
  inline GUI_set* get_gui_set(){return gui_set;}
  inline GUI_camera* get_gui_camera(){return gui_camera;}
  inline GUI_capture* get_gui_capture(){return gui_capture;}
  inline GUI_scene* get_gui_scene(){return gui_scene;}
  inline GUI_engine* get_gui_engine(){return gui_engine;}
  inline GUI_render_option* get_gui_option(){return gui_render_option;}

private:
  GUI* gui;
  GUI_render_panel* gui_render_panel;

  GUI_profiler* gui_profiler;
  GUI_scene* gui_scene;
  GUI_shader* gui_shader;
  GUI_engine* gui_engine;
  GUI_database* gui_database;
  GUI_object* gui_object;
  GUI_camera* gui_camera;
  GUI_capture* gui_capture;
  GUI_set* gui_set;
  GUI_render_option* gui_render_option;
  GUI_render_menu* gui_render_menu;

  bool show_camera;
  bool show_object;
  bool show_set;
};

#endif
