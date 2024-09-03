#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace core{class Node;}
namespace dyn{class Node;}
namespace mod{class Node;}

namespace gui{class Node;}
namespace sce{class Node;}
namespace prf::monitor{class Tasker;}


namespace app{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  //Main function
  void run();

  //Subfunction
  void init();
  void loop();
  void gui();
  void reset();
  void end();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline core::Node* get_node_core(){return node_core;}
  inline mod::Node* get_node_module(){return node_module;}

  inline sce::Node* get_node_scene(){return node_scene;}
  inline void close(){this->running = false;}

private:
  vk::Node* node_vulkan;
  core::Node* node_core;
  dyn::Node* node_dynamic;
  mod::Node* node_module;
  prf::monitor::Tasker* tasker;

  gui::Node* node_gui;
  sce::Node* node_scene;

  bool running = true;
};

}
