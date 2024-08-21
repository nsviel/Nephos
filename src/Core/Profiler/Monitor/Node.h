#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace vk{class Node;}

namespace prf{class Structure;}
namespace prf::hardware{class Manager;}
namespace prf::monitor{class Manager;}
namespace prf::gui{class Panel;}


namespace prf{

class Node : public utl::base::Node
{
public:
  Node(core::Node* node_core);
  ~Node();

public:
  //Main function
  void init();
  void gui();
  void loop();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline prf::Structure* get_prf_struct(){return prf_struct;}
  inline prf::monitor::Manager* get_prf_monitor(){return prf_monitor;}
  inline prf::hardware::Manager* get_prf_hardware(){return prf_hardware;}

private:
  vk::Node* node_vulkan;

  prf::Structure* prf_struct;
  prf::monitor::Manager* prf_monitor;
  prf::hardware::Manager* prf_hardware;
  prf::gui::Panel* gui_panel;
};

}
