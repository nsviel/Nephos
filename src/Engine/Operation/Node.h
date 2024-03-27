#pragma once

#include <Utility/Specific/Common.h>

namespace utl{class Node;}
namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace eng::cam{class Node;}
namespace ope{class Wheel;}
namespace ope::gui{class Control;}


namespace ope{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void gui();
  void control();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::cam::Node* get_node_camera(){return node_camera;}
  inline utl::Node* get_node_utility(){return node_utility;}
  
  inline ope::Wheel* get_ope_wheel(){return ope_wheel;}
  inline ope::gui::Control* get_gui_control(){return gui_control;}

private:
  //Dependancy
  eng::Node* node_engine;
  utl::Node* node_utility;
  eng::scene::Node* node_scene;
  eng::cam::Node* node_camera;

  //Child
  ope::Wheel* ope_wheel;
  ope::gui::Control* gui_control;
};

}
