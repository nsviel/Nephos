#pragma once

#include <Utility/Base/Type/Node.h>
#include <Utility/Specific/Common.h>

namespace app{class Node;}
namespace eng{class Node;}
namespace sce{class Node;}
namespace prf{class Node;}

namespace gui::interface{class Control;}
namespace gui::interface{class Docking;}
namespace gui{class Tab;}
namespace gui::style{class Config;}
namespace gui::style{class Font;}
namespace gui::style{class Theme;}


namespace gui{

class Node : public utl::type::Node
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
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline gui::interface::Control* get_gui_control(){return gui_control;}
  inline gui::style::Config* get_gui_style(){return gui_style;}
  inline gui::Tab* get_gui_tab(){return gui_tab;}
  inline gui::style::Font* get_gui_font(){return gui_font;}

private:
  //Dependancy
  eng::Node* node_engine;
  sce::Node* node_scene;
  prf::Node* node_profiler;

  //Child
  gui::interface::Control* gui_control;
  gui::interface::Docking* gui_docking;
  gui::Tab* gui_tab;
  gui::style::Config* gui_style;
  gui::style::Font* gui_font;
  gui::style::Theme* gui_theme;
};

}
