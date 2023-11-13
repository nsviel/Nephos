#ifndef VK_SUBMIT_H
#define VK_SUBMIT_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_command.h>
#include <VK_struct/Struct_swapchain.h>
#include <UTL_specific/common.h>

class Struct_vulkan;


class VK_submit
{
public:
  //Constructor / Destructor
  VK_submit(Struct_vulkan* struct_vulkan);
  ~VK_submit();

public:
  //Main functions
  void submit_command_graphics(VkCommandBuffer command);
  void submit_command_render(Struct_command* commands);

private:
  Struct_vulkan* struct_vulkan;
};

#endif
