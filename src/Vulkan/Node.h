#pragma once

#include <Utility/Specific/Common.h>

namespace utl{class Node;}
namespace utl::element{class Window;}
namespace vk::main{class Graphical;}
namespace vk::main{class Imgui;}
namespace vk::main{class Info;}
namespace vk::main{class Texture;}
namespace vk::structure{class Vulkan;}
namespace vk::synchro{class Synchro;}
namespace vk::image{class Screenshot;}


namespace vk{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(utl::Node* node_utility);
  ~Node();

public:
  //Main functions
  void init();
  void clean();
  void loop();

  inline vk::structure::Vulkan* get_vk_struct(){return vk_struct;}
  inline vk::main::Graphical* get_vk_graphical(){return vk_graphical;}
  inline vk::main::Imgui* get_vk_imgui(){return vk_imgui;}
  inline vk::main::Info* get_vk_info(){return vk_info;}
  inline vk::main::Texture* get_vk_texture(){return vk_texture;}
  inline vk::image::Screenshot* get_vk_screenshot(){return vk_screenshot;}

private:
  vk::structure::Vulkan* vk_struct;
  vk::main::Graphical* vk_graphical;
  vk::main::Imgui* vk_imgui;
  vk::main::Info* vk_info;
  vk::main::Texture* vk_texture;
  vk::synchro::Synchro* vk_synchro;
  vk::image::Screenshot* vk_screenshot;
};

}
