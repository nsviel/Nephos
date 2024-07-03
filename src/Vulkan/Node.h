#pragma once

#include <Utility/Base/Class/Node.h>

namespace utl{class Node;}
namespace utl::element{class Window;}
namespace vk{class Structure;}
namespace vk::main{class Engine;}
namespace vk::gui{class Imgui;}
namespace vk::main{class Interface;}
namespace vk::image{class Texture;}
namespace vk::synchro{class Synchro;}
namespace vk::image{class Screenshot;}
namespace vk::render{class Render;}
namespace vk::window{class GLFW;}
namespace vk::data{class Data;}


namespace vk{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(bool* running);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void clean();

  inline vk::Structure* get_vk_struct(){return vk_struct;}
  inline vk::gui::Imgui* get_vk_imgui(){return vk_imgui;}
  inline vk::main::Interface* get_vk_interface(){return vk_interface;}
  inline vk::image::Texture* get_vk_texture(){return vk_texture;}
  inline vk::render::Render* get_vk_render(){return vk_render;}
  inline vk::image::Screenshot* get_vk_screenshot(){return vk_screenshot;}
  inline vk::window::GLFW* get_vk_window(){return vk_window;}
  inline vk::data::Data* get_vk_data(){return vk_data;}

private:
  vk::Structure* vk_struct;
  vk::render::Render* vk_render;
  vk::main::Engine* vk_engine;
  vk::gui::Imgui* vk_imgui;
  vk::main::Interface* vk_interface;
  vk::image::Texture* vk_texture;
  vk::synchro::Synchro* vk_synchro;
  vk::image::Screenshot* vk_screenshot;
  vk::window::GLFW* vk_window;
  vk::data::Data* vk_data;
};

}
