#include "VK_viewport.h"

#include <VK_struct/Namespace.h>


//Constructor / Destructor
VK_viewport::VK_viewport(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_viewport::~VK_viewport(){}

//Main function
void VK_viewport::init_viewport(){
  vec2 win_dim = struct_vulkan->window.window_dim;
  //---------------------------

  //Viewport
  struct_vulkan->render.viewport = {};
  struct_vulkan->render.viewport.x = 0;
  struct_vulkan->render.viewport.y = 0;
  struct_vulkan->render.viewport.width  = win_dim.x;
  struct_vulkan->render.viewport.height = win_dim.y;
  struct_vulkan->render.viewport.minDepth = 0.0f;
  struct_vulkan->render.viewport.maxDepth = 1.0f;

  //Full viewport scissor
  struct_vulkan->render.scissor = {};
  struct_vulkan->render.scissor.offset = {0, 0};
  struct_vulkan->render.scissor.extent = struct_vulkan->window.extent;

  //---------------------------
}
void VK_viewport::cmd_viewport(VkCommandBuffer& command_buffer){
  //---------------------------

  //Viewport
  vkCmdSetViewport(command_buffer, 0, 1, &struct_vulkan->render.viewport);

  //Scissor
  vkCmdSetScissor(command_buffer, 0, 1, &struct_vulkan->render.scissor);

  //---------------------------
}
void VK_viewport::update_viewport(){
  vec2 win_dim = struct_vulkan->window.window_dim;
  //---------------------------

  //Viewport scene
  struct_vulkan->render.viewport.x = 0;
  struct_vulkan->render.viewport.y = 0;
  struct_vulkan->render.viewport.width  = win_dim.x;
  struct_vulkan->render.viewport.height = win_dim.y;

  //Scissor
  struct_vulkan->render.scissor.extent = struct_vulkan->window.extent;

  //---------------------------
}

//Subfunction
vk::structure::Viewport* VK_viewport::create_viewport(){
  vec2 win_dim = struct_vulkan->window.window_dim;
  //---------------------------

  //Viewport
  vk::structure::Viewport* viewport = new vk::structure::Viewport();
  viewport->viewport = {};
  viewport->viewport.x = 0;
  viewport->viewport.y = 0;
  viewport->viewport.width  = win_dim.x;
  viewport->viewport.height = win_dim.y;
  viewport->viewport.minDepth = 0.0f;
  viewport->viewport.maxDepth = 1.0f;

  //Full viewport scissor
  viewport->scissor = {};
  viewport->scissor.offset = {0, 0};
  viewport->scissor.extent = struct_vulkan->window.extent;

  //---------------------------
  return viewport;
}
