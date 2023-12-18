#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


class VK_memory;


class VK_buffer
{
public:
  //Constructor / Destructor
  VK_buffer(vk::structure::Vulkan* struct_vulkan);
  ~VK_buffer();

public:
  //Main functions
  void create_buffers(vk::structure::Object* data);
  void clean_buffers(vk::structure::Object* data);
  void clean_buffer(vk::structure::Buffer* buffer);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_memory* vk_memory;
};
