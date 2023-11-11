#ifndef VULKAN_BACKEND_H
#define VULKAN_BACKEND_H

#include <VK_main/Struct_vulkan.h>
#include <ELE_specific/common.h>

class Struct_vulkan;
class ELE_window;
class VK_engine;
class VK_imgui;
class VK_render;
class VK_info;


class Vulkan
{
public:
  //Constructor / Destructor
  Vulkan(ELE_window* window);
  ~Vulkan();

public:
  //Main functions
  void init();
  void clean();
  void loop();
  void wait();
  void param(ELE_window* ele_window, bool headless);

  inline Struct_vulkan* get_struct_vulkan(){return struct_vulkan;}
  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline VK_imgui* get_vk_imgui(){return vk_imgui;}
  inline VK_render* get_vk_render(){return vk_render;}
  inline VK_info* get_vk_info(){return vk_info;}

  inline void set_headless(){struct_vulkan->param.headless = true;}

private:
  ELE_window* ele_window;
  Struct_vulkan* struct_vulkan;
  VK_engine* vk_engine;
  VK_imgui* vk_imgui;
  VK_render* vk_render;
  VK_info* vk_info;
};

#endif
