#pragma once

namespace vk{class Node;}
namespace core{class Node;}
namespace gui{class Node;}
namespace sce{class Node;}
namespace mod{class Node;}


namespace app{

class Node
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
  void end();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline sce::Node* get_node_scene(){return node_scene;}
  inline core::Node* get_node_core(){return node_core;}
  inline void close(){this->running = false;}

private:
  vk::Node* node_vulkan;
  core::Node* node_core;
  gui::Node* node_gui;
  sce::Node* node_scene;
  mod::Node* node_module;

  bool running = true;
};

}
