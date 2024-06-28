#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace cam{class Node;}
namespace itf{class Structure;}
namespace itf::control{class Camera;}
namespace itf::gui{class Camera;}
namespace itf::gui{class Option;}
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
  inline itf::Structure* get_itf_struct(){return itf_struct;}
  inline itf::control::Camera* get_itf_camera(){return itf_camera;}
  inline itf::gui::Camera* get_gui_camera(){return gui_camera;}

private:
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  cam::Node* node_camera;

  itf::Structure* itf_struct;
  itf::control::Camera* itf_camera;
  itf::gui::Camera* gui_camera;
  itf::gui::Option* gui_option;
  itf::gui::Shader* gui_shader;
  itf::gui::Renderer* gui_render;
};

}
