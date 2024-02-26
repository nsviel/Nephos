#pragma once

#include <Utility/Specific/common.h>

class App_main;
namespace eng{class Node;}
namespace utl{class Node;}
namespace utl::element{class Window;}
namespace gui::interface{class Control;}
namespace gui::interface{class Docking;}
namespace gui::interface{class Tab;}
namespace gui::style{class Config;}
namespace gui::style{class Font;}
namespace gui::style{class Theme;}
namespace gui{class Render;}


namespace gui{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(App_main* node_app);
  ~Node();

public:
  void init();
  void loop();
  void exit();

  inline utl::Node* get_node_utility(){return node_utility;}
  inline eng::Node* get_node_engine(){return node_engine;}

  inline gui::interface::Control* get_gui_control(){return gui_control;}
  inline gui::style::Config* get_gui_style(){return gui_style;}
  inline gui::interface::Tab* get_gui_tab(){return gui_tab;}
  inline gui::style::Font* get_gui_font(){return gui_font;}
  inline gui::Render* get_rnd_tab(){return gui_render;}

private:
  //Dependancy
  eng::Node* node_engine;
  utl::Node* node_utility;

  //Child
  gui::interface::Control* gui_control;
  gui::interface::Docking* gui_docking;
  gui::interface::Tab* gui_tab;
  gui::style::Config* gui_style;
  gui::style::Font* gui_font;
  gui::style::Theme* gui_theme;
  gui::Render* gui_render;
};

}
