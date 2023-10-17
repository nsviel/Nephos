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
