#ifndef GUI_NODE_H
#define GUI_NODE_H

#include <Specific/common.h>

class Engine;
class Data;
class Window;

class GUI_font;
class GUI_control_gui;
class GUI_style;
class GUI_init;
class GUI_gpu;
class GUI_image;
class GUI_video;
class GUI_tab;


class GUI
{
public:
  //Constructor / Destructor
  GUI(Window* window, Engine* engine);
  ~GUI();

public:
  void init();
  void loop();
  void exit();

  //Subfunction
  void docker_space_main();

  inline Engine* get_engine(){return engine;}
  inline Data* get_data(){return data;}
  inline Window* get_window(){return window;}

  inline GUI_control_gui* get_gui_control(){return gui_control;}
  inline GUI_style* get_gui_style(){return gui_style;}
  inline GUI_init* get_gui_init(){return gui_init;}
  inline GUI_tab* get_gui_tab(){return gui_tab;}
  inline GUI_font* get_gui_font(){return gui_font;}

private:
  Engine* engine;
  Data* data;
  Window* window;

  GUI_control_gui* gui_control;
  GUI_style* gui_style;
  GUI_init* gui_init;
  GUI_gpu* gui_gpu;
  GUI_font* gui_font;
  GUI_tab* gui_tab;
};

#endif
