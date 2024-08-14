#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace core{class Node;}
namespace cam{class Node;}
namespace dyn{class Node;}
namespace dat{class Node;}
namespace ctl{class Structure;}
namespace ctl::mode{class Navigation;}
namespace ctl::mode{class Edition;}
namespace ctl{class Wheel;}
namespace ctl{class Player;}
namespace ctl::gui{class Control;}


namespace ctl{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  //Subfunction
  inline core::Node* get_node_core(){return node_core;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline cam::Node* get_node_camera(){return node_camera;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}
  inline dat::Node* get_node_data(){return node_data;}
  inline ctl::Structure* get_ctl_struct(){return ctl_struct;}
  inline ctl::mode::Navigation* get_ctl_navigation(){return ctl_navigation;}
  inline ctl::mode::Edition* get_ctl_edition(){return ctl_edition;}
  inline ctl::Wheel* get_ctl_wheel(){return ctl_wheel;}
  inline ctl::Player* get_ctl_player(){return ctl_player;}
  inline ctl::gui::Control* get_gui_control(){return gui_control;}

private:
  core::Node* node_core;
  vk::Node* node_vulkan;
  cam::Node* node_camera;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  ctl::Structure* ctl_struct;
  ctl::mode::Navigation* ctl_navigation;
  ctl::mode::Edition* ctl_edition;
  ctl::Wheel* ctl_wheel;
  ctl::Player* ctl_player;
  ctl::gui::Control* gui_control;
};

}
