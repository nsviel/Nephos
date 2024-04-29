#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Element/Namespace.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace cam{class Control;}
namespace cam{class Manager;}
namespace cam::gui{class Control;}
namespace cam::gui{class Panel;}


namespace cam{

class Node : public utl::type::Node
{
public:
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void control();
  void reset();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}

  inline cam::gui::Control* get_gui_control(){return gui_control;}
  inline cam::Control* get_camera_control(){return cam_control;}
  inline cam::Manager* get_camera_manager(){return cam_manager;}

private:
  //Dependancy
  vk::Node* node_vulkan;
  eng::scene::Node* node_scene;

  //Child
  cam::Control* cam_control;
  cam::Manager* cam_manager;
  cam::gui::Control* gui_control;
  cam::gui::Panel* gui_panel;
};

}
