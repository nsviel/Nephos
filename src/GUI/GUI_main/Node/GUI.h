#pragma once

#include <GUI/GUI_main/Render/Render.h>
#include <GUI/GUI_main/Node/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>

class Engine;
class Node;
class GUI_font;


class GUI
{
public:
  //Constructor / Destructor
  GUI(util::Node* utility, Engine* engine);
  ~GUI();

public:
  void init();
  void loop();
  void exit();
  void wait();

  inline util::Node* get_utility(){return utility;}
  inline Engine* get_engine(){return engine;}

  inline gui::Control* get_gui_control(){return gui_control;}
  inline gui::Style* get_gui_style(){return gui_style;}
  inline gui::Tab* get_gui_tab(){return gui_tab;}
  inline GUI_font* get_gui_font(){return gui_font;}
  inline gui::Render* get_rnd_tab(){return gui_render;}

private:
  Engine* engine;
  Node* eng_data;
  util::Node* utility;

  util::element::Window* utl_window;
  gui::Control* gui_control;
  gui::Style* gui_style;
  gui::Docking* gui_docking;
  GUI_font* gui_font;
  gui::Tab* gui_tab;
  gui::Render* gui_render;
};
