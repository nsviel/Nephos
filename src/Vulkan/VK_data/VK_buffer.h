#pragma once

#include <VK_struct/Namespace.h>
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
  void create_buffers(vk::structure::Entity* data);
  void clean_buffers(vk::structure::Entity* data);
  void clean_buffer(vk::structure::Buffer* buffer);

private:
  Struct_vulkan* struct_vulkan;
  VK_memory* vk_memory;
};
