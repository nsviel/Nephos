#ifndef GUI_NODE_H
#define GUI_NODE_H

#include <GUI_main/GUI_render/GUI_render.h>
#include <UTL_specific/common.h>

class Engine;
class ENG_data;
class UTL_window;

class GUI_font;
class GUI_control;
class GUI_style;
class GUI_gpu;
class GUI_image;
class GUI_tab;
class GUI_render;


class GUI
{
public:
  //Constructor / Destructor
  GUI(UTL_window* utl_window, Engine* engine);
  ~GUI();

public:
  void init();
  void loop();
  void exit();
  void wait();
  void resize();

  //Subfunction
  void docker_space_main();

  inline Engine* get_engine(){return engine;}
  inline UTL_window* get_ele_window(){return utl_window;}

  inline GUI_control* get_gui_control(){return gui_control;}
  inline GUI_style* get_gui_style(){return gui_style;}
  inline GUI_tab* get_gui_tab(){return gui_tab;}
  inline GUI_font* get_gui_font(){return gui_font;}
  inline GUI_render* get_gui_render(){return gui_render;}

private:
  Engine* engine;
  ENG_data* eng_data;
  UTL_window* utl_window;

  GUI_control* gui_control;
  GUI_style* gui_style;
  GUI_gpu* gui_gpu;
  GUI_font* gui_font;
  GUI_tab* gui_tab;
  GUI_render* gui_render;
};

#endif
