#pragma once

#include <Utility/Base/Class/Node.h>

namespace sys{class Node;}
namespace vk{class Node;}

namespace prf::hardware{class Node;}
namespace prf::monitor{class Node;}
namespace prf::monitor{class Tasker;}
namespace prf::gui{class Panel;}


namespace prf{

class Node : public utl::base::Node
{
public:
  Node(sys::Node* node_system);
  ~Node();

public:
  //Main function
  void init();
  void gui();
  void loop();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline prf::hardware::Node* get_node_hardware(){return node_hardware;}
  inline prf::monitor::Node* get_node_monitor(){return node_monitor;}
  inline prf::monitor::Tasker* get_tasker_cpu(){return tasker_cpu;}

private:
  vk::Node* node_vulkan;

  prf::monitor::Node* node_monitor;
  prf::monitor::Tasker* tasker_cpu;
  prf::hardware::Node* node_hardware;
  prf::gui::Panel* gui_panel;
};

}
