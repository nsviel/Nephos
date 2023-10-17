#ifndef GUI_NODE_H
#define GUI_NODE_H

#include <Specific/common.h>

class Engine;
class Data;
class Window;

class GUI_panel;
class GUI_control;
class GUI_mainmenubar;
class GUI_style;
class GUI_init;
class GUI_gpu;
class GUI_image;
class GUI_video;


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

  inline GUI_panel* get_gui_panel(){return gui_panel;}
  inline GUI_control* get_gui_control(){return gui_control;}
  inline GUI_mainmenubar* get_gui_menubar(){return gui_menubar;}
  inline GUI_style* get_gui_style(){return gui_style;}
  inline GUI_init* get_gui_init(){return gui_init;}
  inline GUI_image* get_gui_image(){return gui_image;}
  inline GUI_video* get_gui_video(){return gui_video;}

private:
  Engine* engine;
  Data* data;
  Window* window;

  GUI_panel* gui_panel;
  GUI_control* gui_control;
  GUI_mainmenubar* gui_menubar;
  GUI_style* gui_style;
  GUI_init* gui_init;
  GUI_gpu* gui_gpu;
  GUI_image* gui_image;
  GUI_video* gui_video;
};

#endif
