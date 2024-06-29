#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace cam{class Node;}
namespace dyn{class Node;}
namespace dat{class Node;}
namespace itf{class Structure;}
namespace itf::control{class Camera;}
namespace itf::control{class Wheel;}
namespace itf::control{class Element;}
namespace itf::gui{class Navigation;}
namespace itf::gui{class Option;}
namespace itf::gui{class Player;}
namespace itf::gui{class Shader;}
namespace itf::gui{class Renderer;}
namespace itf::gui{class Edition;}


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
  inline itf::control::Camera* get_itf_camera(){return itf_camera;}
  inline itf::control::Wheel* get_itf_wheel(){return itf_wheel;}
  inline itf::control::Element* get_itf_element(){return itf_element;}
  inline itf::gui::Navigation* get_gui_navigation(){return gui_navigation;}
  inline itf::gui::Edition* get_gui_edition(){return gui_edition;}
  inline itf::gui::Player* get_gui_player(){return gui_player;}

private:
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  cam::Node* node_camera;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  itf::Structure* itf_struct;
  itf::control::Camera* itf_camera;
  itf::control::Wheel* itf_wheel;
  itf::control::Element* itf_element;
  itf::gui::Navigation* gui_navigation;
  itf::gui::Player* gui_player;
  itf::gui::Option* gui_option;
  itf::gui::Shader* gui_shader;
  itf::gui::Renderer* gui_render;
  itf::gui::Edition* gui_edition;
};

}
