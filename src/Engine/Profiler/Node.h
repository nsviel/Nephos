#pragma once

#include <Utility/Base/Type/Node.h>

namespace eng{class Node;}
namespace vk{class Node;}
namespace prf::dynamic{class Manager;}
namespace prf{class Structure;}
namespace prf::hardware{class Profiler;}
namespace prf::gui{class Panel;}


namespace prf{

class Node : public utl::base::Node
{
public:
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();
  void loop();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline prf::Structure* get_prf_struct(){return prf_struct;}
  inline prf::dynamic::Manager* get_prf_manager(){return prf_manager;}
  inline prf::hardware::Profiler* get_prf_hardware(){return prf_hardware;}

private:
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  prf::Structure* prf_struct;
  prf::dynamic::Manager* prf_manager;
  prf::hardware::Profiler* prf_hardware;
  prf::gui::Panel* gui_panel;
};

}
