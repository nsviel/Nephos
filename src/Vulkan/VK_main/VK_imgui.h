#ifndef VK_IMGUI_H
#define VK_IMGUI_H

#include <ELE_specific/common.h>

class Window;
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
  void load_font();
  void clean();
  ImTextureID engine_texture();

private:
  Window* window;
  Struct_vulkan* struct_vulkan;

  VkDescriptorPool descriptor_pool;
};

#endif
