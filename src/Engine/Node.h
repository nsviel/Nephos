#pragma once

#include <Utility/Specific/common.h>

class Param;
namespace vk{class Node;}
namespace utl{class Node;}
namespace prf{class Node;}
namespace prf{class Tasker;}
namespace eng::cam{class Node;}
namespace eng::scene{class Node;}
namespace eng::render{class Node;}
namespace eng::capture{class Node;}
namespace eng::ope{class Node;}
namespace eng::gui{class Node;}


namespace eng{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(utl::Node* node_utility);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void exit();
  void reset();
  void wait();

  inline utl::Node* get_node_utility(){return node_utility;}
  inline vk::Node* get_eng_vulkan(){return eng_vulkan;}
  inline prf::Tasker* get_tasker_cpu(){return tasker_cpu;}
  inline eng::cam::Node* get_node_camera(){return node_camera;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::render::Node* get_node_render(){return node_render;}
  inline eng::capture::Node* get_node_capture(){return node_capture;}
  inline eng::ope::Node* get_node_operation(){return node_operation;}

private:
  vk::Node* eng_vulkan;
  utl::Node* node_utility;
  prf::Node* node_profiler;
  prf::Tasker* tasker_cpu;
  eng::cam::Node* node_camera;
  eng::scene::Node* node_scene;
  eng::capture::Node* node_capture;
  eng::render::Node* node_render;
  eng::ope::Node* node_operation;
  eng::gui::Node* node_gui;
};

}
