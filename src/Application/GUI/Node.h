#pragma once

#include <Utility/Base/Class/Node.h>

namespace app{class Node;}
namespace core{class Node;}
namespace sce{class Node;}
namespace vk{class Node;}

namespace gui{class Layout;}
namespace gui::state{class Manager;}
namespace gui::style{class Style;}
namespace gui::style{class Font;}
namespace gui::style{class Theme;}
namespace gui::menu{class Demo;}


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
  void gui();

  inline core::Node* get_node_core(){return node_core;}
  inline sce::Node* get_node_scene(){return node_scene;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline gui::menu::Demo* get_gui_demo(){return gui_demo;}
  inline gui::state::Manager* get_gui_state(){return gui_state;}
  inline gui::style::Font* get_gui_font(){return gui_font;}

private:
  //Dependancy
  core::Node* node_core;
  sce::Node* node_scene;
  vk::Node* node_vulkan;

  //Child
  gui::Layout* gui_layout;
  gui::menu::Demo* gui_demo;
  gui::state::Manager* gui_state;
  gui::style::Style* gui_style;
  gui::style::Font* gui_font;
  gui::style::Theme* gui_theme;
};

}
