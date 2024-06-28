#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace cam{class Node;}
namespace dat{class Node;}
namespace itf{class Structure;}
namespace itf::control{class Camera;}
namespace itf::control{class Wheel;}
namespace itf::gui{class Camera;}
namespace itf::gui{class Option;}
namespace itf::gui{class Shader;}
namespace itf::gui{class Renderer;}
namespace itf::gui{class Element;}


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
  inline dat::Node* get_node_data(){return node_data;}
  inline itf::Structure* get_itf_struct(){return itf_struct;}
  inline itf::control::Camera* get_itf_camera(){return itf_camera;}
  inline itf::control::Wheel* get_itf_wheel(){return itf_wheel;}
  inline itf::gui::Camera* get_gui_camera(){return gui_camera;}
  inline itf::gui::Element* get_gui_element(){return gui_element;}

private:
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  cam::Node* node_camera;
  dat::Node* node_data;

  itf::Structure* itf_struct;
  itf::control::Camera* itf_camera;
  itf::control::Wheel* itf_wheel;
  itf::gui::Camera* gui_camera;
  itf::gui::Option* gui_option;
  itf::gui::Shader* gui_shader;
  itf::gui::Renderer* gui_render;
  itf::gui::Element* gui_element;
};

}
