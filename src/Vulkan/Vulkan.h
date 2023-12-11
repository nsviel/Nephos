#pragma once

#include <VK_main/Struct_vulkan.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class UTL_window;
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
  void param(UTL_window* utl_window, bool headless);

  inline Struct_vulkan* get_struct_vulkan(){return struct_vulkan;}
  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline VK_imgui* get_vk_imgui(){return vk_imgui;}
  inline VK_info* get_vk_info(){return vk_info;}
  inline VK_texture* get_vk_texture(){return vk_texture;}

  inline void set_headless(bool value){struct_vulkan->param.headless = value;}
  inline void set_name(string value){struct_vulkan->name = value;}
  inline void set_prefere_dedicated_gpu(bool value){struct_vulkan->param.dedicated_gpu = value;}

private:
  UTL_window* utl_window;
  Struct_vulkan* struct_vulkan;
  VK_engine* vk_engine;
  VK_imgui* vk_imgui;
  VK_info* vk_info;
  VK_texture* vk_texture;
};
