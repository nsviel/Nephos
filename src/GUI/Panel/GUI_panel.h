#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include <Specific/common.h>

class GUI;
class Panel;

class GUI_profiler;
class GUI_scene;
class GUI_mainmenubar;
class GUI_shader;
class GUI_engine;
class GUI;
class GUI_database;
class GUI_camera;
class GUI_object;
class GUI_set;
class GUI_capture;


class GUI_panel
{
public:
  //Constructor / Destructor
  GUI_panel(GUI* gui);
  ~GUI_panel();

public:
  //Main functions
  void draw_panels();
  void open_panels();

  inline Panel* get_panel(){return panel;}
  inline GUI_shader* get_gui_shader(){return gui_shader;}
  inline GUI_profiler* get_gui_profiling(){return gui_profiler;}
  inline GUI_object* get_gui_object(){return gui_object;}
  inline GUI_set* get_gui_set(){return gui_set;}
  inline GUI_camera* get_gui_camera(){return gui_camera;}
  inline GUI_capture* get_gui_capture(){return gui_capture;}
  inline GUI_scene* get_gui_scene(){return gui_scene;}
  inline GUI_engine* get_gui_engine(){return gui_engine;}

private:
  GUI* gui;
  Panel* panel;

  GUI_profiler* gui_profiler;
  GUI_scene* gui_scene;
  GUI_mainmenubar* gui_menubar;
  GUI_shader* gui_shader;
  GUI_engine* gui_engine;
  GUI_database* gui_database;
  GUI_object* gui_object;
  GUI_camera* gui_camera;
  GUI_capture* gui_capture;
  GUI_set* gui_set;

  bool show_camera;
  bool show_object;
  bool show_set;
};

#endif
