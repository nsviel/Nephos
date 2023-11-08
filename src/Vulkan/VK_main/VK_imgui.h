#ifndef VK_IMGUI_H
#define VK_IMGUI_H

#include <VK_struct/Struct_subpass.h>
#include <ELE_specific/common.h>

class ELE_window;
class VK_engine;
class Struct_vulkan;


class VK_imgui
{
public:
  //Constructor / Destructor
  VK_imgui(VK_engine* vk_engine);
  ~VK_imgui();

public:
  //Main functions
  void init();
  void draw(Struct_subpass* subpass);
  void load_font();
  void clean();
  ImTextureID engine_texture();

private:
  ELE_window* ele_window;
  Struct_vulkan* struct_vulkan;

  VkDescriptorPool descriptor_pool;
};

#endif
