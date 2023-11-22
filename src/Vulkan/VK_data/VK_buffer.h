#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include <VK_struct/Struct_vk_entity.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_memory;


class VK_buffer
{
public:
  //Constructor / Destructor
  VK_buffer(Struct_vulkan* struct_vulkan);
  ~VK_buffer();

public:
  //Main functions
  void create_buffers(Struct_vk_entity* data);
  void clean_buffers(Struct_vk_entity* data);
  void clean_buffer(Struct_vk_buffer* buffer);

private:
  Struct_vulkan* struct_vulkan;
  VK_memory* vk_memory;
};

#endif
