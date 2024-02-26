#pragma once

#include <Utility/Specific/common.h>

class App_main;
namespace vk{class Node;}
namespace utl{class Node;}
namespace prf{class Node;}
namespace prf::graph{class Tasker;}
namespace eng::cam{class Node;}
namespace eng::scene{class Node;}
namespace eng::render{class Node;}
namespace eng::capture{class Node;}
namespace ope{class Node;}
namespace eng::gui{class Node;}


namespace eng{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(App_main* node_app);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void clean();
  void reset();

  inline utl::Node* get_node_utility(){return node_utility;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline eng::cam::Node* get_node_camera(){return node_camera;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::render::Node* get_node_render(){return node_render;}
  inline eng::capture::Node* get_node_capture(){return node_capture;}
  inline ope::Node* get_node_operation(){return node_operation;}

private:
  //Dependancy
  utl::Node* node_utility;
  prf::Node* node_profiler;

  //Child
  vk::Node* node_vulkan;
  prf::graph::Tasker* tasker_main;
  eng::cam::Node* node_camera;
  eng::scene::Node* node_scene;
  eng::capture::Node* node_capture;
  eng::render::Node* node_render;
  ope::Node* node_operation;
  eng::gui::Node* node_gui;
};

}
