#ifndef VK_IMGUI_H
#define VK_IMGUI_H

#include <VK_struct/Struct_subpass.h>
#include <VK_struct/Struct_image.h>
#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_engine;
class VK_pool;
class VK_submit;
class VK_command;
class VK_image;
class VK_texture;
class VK_buffer;
class VK_framebuffer;
class VK_physical_device;


class VK_imgui
{
public:
  //Constructor / Destructor
  VK_imgui(Struct_vulkan* struct_vulkan);
  ~VK_imgui();

public:
  //Main functions
  void init();
  void draw(VkCommandBuffer& command_buffer);
  void load_font();
  void clean();
  Struct_image* engine_texture(vec2 dim);
VkDeviceSize calculateImageSize(VkFormat format, VkExtent3D extent);
private:
  Struct_vulkan* struct_vulkan;
  VK_engine* vk_engine;
  VK_submit* vk_submit;
  VK_command* vk_command;
  VK_pool* vk_pool;
  VK_image* vk_image;
  VK_texture* vk_texture;
  VK_buffer* vk_buffer;
  VK_framebuffer* vk_framebuffer;
  VK_physical_device* vk_physical_device;
};

#endif
