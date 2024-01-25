#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace utl{class Node;}
namespace utl::element{class Window;}
namespace gui{class Control;}
namespace gui{class Style;}
namespace gui{class Tab;}
namespace gui{class Render;}
namespace gui{class Docking;}
namespace gui::style{class Font;}


namespace gui{

class Node
{
public:
  //Constructor / Destructor
  Node(utl::Node* utility, eng::Node* engine);
  ~Node();

public:
  void init();
  void loop();
  void exit();
  void wait();

  inline utl::Node* get_node_utility(){return utility;}
  inline eng::Node* get_engine(){return engine;}
  inline gui::Control* get_gui_control(){return gui_control;}
  inline gui::Style* get_gui_style(){return gui_style;}
  inline gui::Tab* get_gui_tab(){return gui_tab;}
  inline gui::style::Font* get_gui_font(){return gui_font;}
  inline gui::Render* get_rnd_tab(){return gui_render;}

private:
  eng::Node* engine;
  Node* eng_data;
  utl::Node* utility;

  utl::element::Window* utl_window;
  gui::Control* gui_control;
  gui::Style* gui_style;
  gui::Docking* gui_docking;
  gui::style::Font* gui_font;
  gui::Tab* gui_tab;
  gui::Render* gui_render;
};

}
