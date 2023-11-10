#ifndef VK_IMGUI_H
#define VK_IMGUI_H

#include <VK_struct/Struct_subpass.h>
#include <ELE_specific/common.h>

class VK_engine;
class VK_command_buffer;
class Struct_vulkan;


class VK_imgui
{
public:
  //Constructor / Destructor
  VK_imgui(Struct_vulkan* struct_vulkan);
  ~VK_imgui();

public:
  //Main functions
  void init();
  void draw(Struct_subpass* subpass);
  void load_font();
  void clean();
  ImTextureID engine_texture();

private:
  Struct_vulkan* struct_vulkan;
  VK_command_buffer* vk_command_buffer;
};

#endif
