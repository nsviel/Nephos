#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

class VK_engine;
class VK_imgui;
class VK_info;
class VK_texture;


class Vulkan
{
public:
  //Constructor / Destructor
  Vulkan(GLFWwindow* window);
  ~Vulkan();

public:
  //Main functions
  void init();
  void clean();
  void loop();
  void wait();
  void param(utl::element::Window* utl_window, bool headless);

  inline vk::structure::Vulkan* get_struct_vulkan(){return struct_vulkan;}
  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline VK_imgui* get_vk_imgui(){return vk_imgui;}
  inline VK_info* get_vk_info(){return vk_info;}
  inline VK_texture* get_vk_texture(){return vk_texture;}

  inline void set_headless(bool value){struct_vulkan->param.headless = value;}
  inline void set_name(string value){struct_vulkan->name = value;}
  inline void set_prefere_dedicated_gpu(bool value){struct_vulkan->param.dedicated_gpu = value;}

private:
  utl::element::Window* utl_window;
  vk::structure::Vulkan* struct_vulkan;
  VK_engine* vk_engine;
  VK_imgui* vk_imgui;
  VK_info* vk_info;
  VK_texture* vk_texture;
};
