#pragma once

#include <string>

namespace itf{class Node;}
namespace itf::control{class Camera;}
namespace vk::gui{class Imgui;}
namespace vk::main{class Interface;}
namespace vk{class Structure;}
namespace eng{class Node;}
namespace itf::gui{class Camera;}
namespace itf::gui{class Element;}
namespace dyn::gui{class Control;}


namespace itf::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(itf::Node* node_interface);
  ~Renderer();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void engine_texture();
  void resize();

private:
  itf::gui::Camera* cam_control;
  itf::control::Camera* itf_camera;
  itf::gui::Element* itf_element;
  dyn::gui::Control* dyn_control;
  vk::gui::Imgui* vk_imgui;
  vk::main::Interface* vk_interface;
  vk::Structure* vk_struct;

  std::string name;
  bool has_been_initialized;
};

}
