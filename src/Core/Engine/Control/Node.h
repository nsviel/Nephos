#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace cam{class Node;}
namespace dat{class Node;}
namespace ctr{class Structure;}
namespace ctr{class Wheel;}
namespace ctr{class Player;}
namespace ctr::mode{class Navigation;}
namespace ctr::mode{class Edition;}
namespace ctr::gui{class Control;}


namespace ctr{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void reset();
  void close();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline cam::Node* get_node_camera(){return node_camera;}
  inline dat::Node* get_node_data(){return node_data;}

  inline ctr::Structure* get_ctr_struct(){return ctr_struct;}
  inline ctr::mode::Navigation* get_ctr_navigation(){return ctr_navigation;}
  inline ctr::mode::Edition* get_ctr_edition(){return ctr_edition;}
  inline ctr::Wheel* get_ctr_wheel(){return ctr_wheel;}
  inline ctr::Player* get_ctr_player(){return ctr_player;}
  inline ctr::gui::Control* get_gui_control(){return gui_control;}

private:
  vk::Node* node_vulkan;
  cam::Node* node_camera;
  dat::Node* node_data;

  ctr::Structure* ctr_struct;
  ctr::mode::Navigation* ctr_navigation;
  ctr::mode::Edition* ctr_edition;
  ctr::Wheel* ctr_wheel;
  ctr::Player* ctr_player;
  ctr::gui::Control* gui_control;
};

}
