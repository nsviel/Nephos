#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace ope{class Node;}
namespace eng::gui{class Option;}


namespace eng::gui{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main functions
  void gui();

  //Subfunction
  void draw_menu();
  void menu_panel();
  void menu_loader();
  void menu_screenshot();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline ope::Node* get_node_operation(){return node_operation;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  ope::Node* node_operation;

  //Child
  eng::gui::Option* gui_option;
};

}
