#pragma once

#include <Utility/Specific/common.h>

class VK_engine;
class VK_imgui;
class VK_info;
class VK_texture;
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
  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline VK_imgui* get_vk_imgui(){return vk_imgui;}
  inline VK_info* get_vk_info(){return vk_info;}
  inline VK_texture* get_vk_texture(){return vk_texture;}

private:
  utl::element::Window* utl_window;
  vk::structure::Vulkan* struct_vulkan;
  VK_engine* vk_engine;
  VK_imgui* vk_imgui;
  VK_info* vk_info;
  VK_texture* vk_texture;
};

}
