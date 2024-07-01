#pragma once

#include <Utility/Base/Type/Node.h>

namespace app{class Node;}
namespace eng{class Node;}
namespace sce{class Node;}

namespace gui{class Tab;}
namespace gui::interface{class Demo;}
namespace gui::interface{class Docking;}
namespace gui::state{class Manager;}
namespace gui::style{class Style;}
namespace gui::style{class Font;}
namespace gui::style{class Theme;}
namespace prf::dynamic{class Tasker;}


namespace gui{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  void init();
  void loop();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline sce::Node* get_node_scene(){return node_scene;}

  inline gui::Tab* get_gui_tab(){return gui_tab;}
  inline gui::interface::Demo* get_gui_demo(){return gui_demo;}
  inline gui::state::Manager* get_gui_state(){return gui_state;}
  inline gui::style::Font* get_gui_font(){return gui_font;}

private:
  //Dependancy
  eng::Node* node_engine;
  sce::Node* node_scene;

  //Child
  gui::Tab* gui_tab;
  gui::interface::Demo* gui_demo;
  gui::interface::Docking* gui_docking;
  gui::state::Manager* gui_state;
  gui::style::Style* gui_style;
  gui::style::Font* gui_font;
  gui::style::Theme* gui_theme;
  prf::dynamic::Tasker* tasker;
};

}
