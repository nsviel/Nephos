#pragma once

namespace vk{class Node;}
namespace eng{class Node;}
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
  inline eng::Node* get_node_engine(){return node_engine;}
  inline void close(){this->running = false;}

private:
  vk::Node* node_vulkan;
  eng::Node* node_engine;
  gui::Node* node_gui;
  sce::Node* node_scene;
  mod::Node* node_module;

  bool running = true;
};

}
