#ifndef VK_MEMORY_H
#define VK_MEMORY_H

#include <VK_struct/Struct_vk_image.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_buffer;
class VK_command;


class VK_memory
{
public:
  //Constructor / Destructor
  VK_memory(Struct_vulkan* struct_vulkan);
  ~VK_memory();

public:
  //Main functions
  void transfert_image_to_gpu(Struct_vk_image* image);
  void copy_buffer_to_image(Struct_vk_image* image, VkBuffer buffer);
  void copy_image_to_buffer(Struct_vk_image* image, VkBuffer buffer);

private:
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_command* vk_command;
};

#endif
