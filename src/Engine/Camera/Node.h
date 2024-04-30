#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace sce{class Node;}
namespace cam{class Control;}
namespace cam{class Manager;}
namespace cam::gui{class Control;}
namespace cam::gui{class Panel;}


namespace cam{

class Node : public utl::type::Node
{
public:
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void reset();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline eng::Node* get_node_engine(){return node_engine;}
  inline dat::Node* get_node_data(){return node_data;}

  inline cam::gui::Control* get_gui_control(){return gui_control;}
  inline cam::Control* get_control(){return cam_control;}
  inline cam::Manager* get_manager(){return cam_manager;}

private:
  //Dependancy
  vk::Node* node_vulkan;
  eng::Node* node_engine;
  dat::Node* node_data;

  //Child
  cam::Control* cam_control;
  cam::Manager* cam_manager;
  cam::gui::Control* gui_control;
  cam::gui::Panel* gui_panel;
};

}
