#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Engine;}
namespace vk::main{class Imgui;}
namespace vk::main{class VK_info;}
namespace vk::main{class VK_texture;}
namespace utl::element{class Window;}
namespace vk::structure{class Vulkan;}


namespace vk{

class Node
{
public:
  //Constructor / Destructor
  Node(GLFWwindow* window);
  ~Node();

public:
  //Main functions
  void init();
  void clean();
  void loop();
  void wait();

  //Parameter function
  void param(utl::element::Window* utl_window, bool headless);

  inline vk::structure::Vulkan* get_struct_vulkan(){return struct_vulkan;}
  inline vk::main::Engine* get_vk_engine(){return vk_engine;}
  inline vk::main::Imgui* get_vk_imgui(){return vk_imgui;}
  inline vk::main::VK_info* get_vk_info(){return vk_info;}
  inline vk::main::VK_texture* get_vk_texture(){return vk_texture;}

private:
  utl::element::Window* utl_window;
  vk::structure::Vulkan* struct_vulkan;
  vk::main::Engine* vk_engine;
  vk::main::Imgui* vk_imgui;
  vk::main::VK_info* vk_info;
  vk::main::VK_texture* vk_texture;
};

}
