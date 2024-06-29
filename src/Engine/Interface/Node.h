#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace cam{class Node;}
namespace dyn{class Node;}
namespace dat{class Node;}
namespace itf{class Structure;}
namespace itf::control{class Navigation;}
namespace itf::control{class Wheel;}
namespace itf::control{class Player;}
namespace itf::control{class Edition;}
namespace itf::render{class Shader;}
namespace itf::gui{class Option;}
namespace itf::gui{class Control;}
namespace itf::gui{class Shader;}
namespace itf::gui{class Renderer;}


namespace itf{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  //Subfunction
  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline cam::Node* get_node_camera(){return node_camera;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}
  inline dat::Node* get_node_data(){return node_data;}
  inline itf::Structure* get_itf_struct(){return itf_struct;}
  inline itf::control::Navigation* get_itf_navigation(){return itf_navigation;}
  inline itf::control::Wheel* get_itf_wheel(){return itf_wheel;}
  inline itf::control::Player* get_itf_player(){return itf_player;}
  inline itf::control::Edition* get_itf_edition(){return itf_edition;}
  inline itf::render::Shader* get_itf_shader(){return itf_shader;}
  inline itf::gui::Control* get_gui_control(){return gui_control;}

private:
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  cam::Node* node_camera;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  itf::Structure* itf_struct;
  itf::control::Navigation* itf_navigation;
  itf::control::Wheel* itf_wheel;
  itf::control::Player* itf_player;
  itf::control::Edition* itf_edition;
  itf::render::Shader* itf_shader;
  itf::gui::Control* gui_control;
  itf::gui::Option* gui_option;
  itf::gui::Shader* gui_shader;
  itf::gui::Renderer* gui_render;

};

}
