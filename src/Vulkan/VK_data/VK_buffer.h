#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class VK_memory;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}
namespace vk::structure{class Buffer;}


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
  vk::command::VK_memory* vk_memory;
};
