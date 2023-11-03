#ifndef VK_SUBMIT_H
#define VK_SUBMIT_H

#include "../VK_struct/struct_frame.h"
#include "../VK_struct/struct_renderpass.h"
#include "../VK_struct/struct_command.h"
#include "../VK_struct/struct_swapchain.h"
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_surface;
class VK_swapchain;
class VK_command;
class VK_cmd;
class VK_descriptor;


class VK_submit
{
public:
  //Constructor / Destructor
  VK_submit(VK_engine* vk_engine);
  ~VK_submit();

public:
  //Main functions
  void acquire_next_image(Struct_swapchain* swapchain);
  void set_next_frame_ID(Struct_swapchain* swapchain);

  //Queue submission
  void submit_graphics_command(Struct_submit_command* command);
  void submit_graphics_command(Struct_renderpass* renderpass);
  void submit_graphics_commands(Struct_submit_commands* commands);
  void submit_presentation(Struct_swapchain* swapchain);

private:
  VK_engine* vk_engine;
  Struct_vulkan* vk_struct;
  VK_surface* vk_surface;
  VK_swapchain* vk_swapchain;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;

  vector<Struct_renderpass*> vec_renderpass;
};

#endif
