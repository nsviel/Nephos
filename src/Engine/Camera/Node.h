#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

namespace utl{class Node;}
namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace eng::cam{class Control;}
namespace eng::cam{class Manager;}
namespace eng::cam::gui{class Control;}
namespace eng::cam::gui{class Panel;}


namespace eng::cam{

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

  inline utl::Node* get_node_utility(){return node_utility;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::cam::Control* get_camera_control(){return cam_control;}
  inline eng::cam::Manager* get_camera_manager(){return cam_manager;}

private:
  //Dependancies
  utl::Node* node_utility;
  eng::scene::Node* node_scene;

  //Subnodes
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
  eng::cam::gui::Control* gui_control;
  eng::cam::gui::Panel* gui_panel;
};

}
