#pragma once

#include <Utility/Specific/common.h>

class Param;
namespace vk{class Vulkan;}
namespace utl{class Node;}
namespace eng::cam{class Node;}
namespace eng::scene{class Node;}
namespace eng::render{class Node;}
namespace eng::capture{class Node;}
namespace eng::ope{class Node;}


namespace eng{

class Node
{
public:
  //Constructor / Destructor
  Node(utl::Node* node_utility);
  ~Node();

public:
  void init();
  void loop();
  void gui();
  void exit();
  void reset();
  void wait();

  inline utl::Node* get_node_utility(){return node_utility;}
  inline vk::Vulkan* get_eng_vulkan(){return eng_vulkan;}
  inline eng::cam::Node* get_node_camera(){return node_camera;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::render::Node* get_node_render(){return node_render;}
  inline eng::capture::Node* get_node_capture(){return node_capture;}

private:
  vk::Vulkan* eng_vulkan;
  utl::Node* node_utility;
  eng::cam::Node* node_camera;
  eng::scene::Node* node_scene;
  eng::capture::Node* node_capture;
  eng::render::Node* node_render;
  eng::ope::Node* node_operation;
};

}
