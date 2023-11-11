#ifndef VK_COMMAND_BUFFER_H
#define VK_COMMAND_BUFFER_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_data.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_physical_device;


class VK_command_buffer
{
public:
  //Constructor / Destructor
  VK_command_buffer(Struct_vulkan* struct_vulkan);
  ~VK_command_buffer();

public:
  //Command buffer
  void allocate_command_buffer_primary(VkCommandBuffer& command_buffer);
  void allocate_command_buffer_secondary(Struct_data* data);

private:
  Struct_vulkan* struct_vulkan;
  VK_physical_device* vk_physical_device;
};

#endif
