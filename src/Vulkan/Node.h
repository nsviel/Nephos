#pragma once

#include <Utility/Specific/Common.h>

namespace app{class Node;}
namespace utl{class Node;}
namespace utl::element{class Window;}
namespace vk::main{class Engine;}
namespace vk::gui{class Imgui;}
namespace vk::main{class Interface;}
namespace vk::image{class Texture;}
namespace vk::structure{class Vulkan;}
namespace vk::synchro{class Synchro;}
namespace vk::image{class Screenshot;}
namespace vk::render{class Manager;}
namespace vk::window{class GLFW;}


namespace vk{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  //Main functions
  void init();
  void loop();
  void reset();
  void clean();

  inline vk::structure::Vulkan* get_vk_struct(){return vk_struct;}
  inline vk::main::Engine* get_vk_engine(){return vk_engine;}
  inline vk::gui::Imgui* get_vk_imgui(){return vk_imgui;}
  inline vk::main::Interface* get_vk_interface(){return vk_interface;}
  inline vk::image::Texture* get_vk_texture(){return vk_texture;}
  inline vk::image::Screenshot* get_vk_screenshot(){return vk_screenshot;}
  inline vk::window::GLFW* get_vk_window(){return vk_window;}

private:
  vk::structure::Vulkan* vk_struct;
  vk::render::Manager* vk_render;
  vk::main::Engine* vk_engine;
  vk::gui::Imgui* vk_imgui;
  vk::main::Interface* vk_interface;
  vk::image::Texture* vk_texture;
  vk::synchro::Synchro* vk_synchro;
  vk::image::Screenshot* vk_screenshot;
  vk::window::GLFW* vk_window;
};

}
