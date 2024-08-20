#pragma once

#include <Utility/Base/Class/Node.h>

namespace mod{class Node;}
namespace prf{class Node;}
namespace core{class Node;}
namespace dat{class Node;}
namespace vk{class Node;}

namespace rad::cor{class Node;}
namespace rad::cal{class Node;}
namespace rad::gui{class Panel;}


namespace rad{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(mod::Node* node_module);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();

  inline core::Node* get_node_core(){return node_core;}
  inline dat::Node* get_node_data(){return node_data;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline rad::cor::Node* get_node_correction(){return node_correction;}
  inline rad::cal::Node* get_node_calibration(){return node_calibration;}

private:
  //Dependancy
  core::Node* node_core;
  dat::Node* node_data;
  vk::Node* node_vulkan;
  prf::Node* node_profiler;

  //Child
  rad::cor::Node* node_correction;
  rad::cal::Node* node_calibration;
  rad::gui::Panel* gui_panel;
};

}
