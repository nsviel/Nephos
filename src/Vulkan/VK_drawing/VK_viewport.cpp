#include "VK_viewport.h"

#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <ELE_window/ELE_window.h>


//Constructor / Destructor
VK_viewport::VK_viewport(VK_engine* vk_engine){
  //---------------------------

  this->ele_window = vk_engine->get_ele_window();
  this->struct_vulkan = vk_engine->get_struct_vulkan();

  //---------------------------
}
VK_viewport::~VK_viewport(){}

//Main function
void VK_viewport::init_viewport(){
  vec2 win_dim = ele_window->get_window_dim();
  //---------------------------

  //Viewport
  struct_vulkan->viewport = {};
  struct_vulkan->viewport.x = 0;
  struct_vulkan->viewport.y = 0;
  struct_vulkan->viewport.width  = win_dim.x;
  struct_vulkan->viewport.height = win_dim.y;
  struct_vulkan->viewport.minDepth = 0.0f;
  struct_vulkan->viewport.maxDepth = 1.0f;

  //Full viewport scissor
  struct_vulkan->scissor = {};
  struct_vulkan->scissor.offset = {0, 0};
  struct_vulkan->scissor.extent = struct_vulkan->window.extent;

  //---------------------------
}
void VK_viewport::cmd_viewport(Struct_subpass* subpass){
  //---------------------------

  //Viewport
  vkCmdSetViewport(subpass->command_buffer, 0, 1, &struct_vulkan->viewport);

  //Scissor
  vkCmdSetScissor(subpass->command_buffer, 0, 1, &struct_vulkan->scissor);

  //---------------------------
}
void VK_viewport::update_viewport(){
  vec2 win_dim = ele_window->get_window_dim();
  //---------------------------

  //Viewport scene
  struct_vulkan->viewport.x = 0;
  struct_vulkan->viewport.y = 0;
  struct_vulkan->viewport.width  = win_dim.x;
  struct_vulkan->viewport.height = win_dim.y;

  //Scissor
  struct_vulkan->scissor.extent = struct_vulkan->window.extent;

  //---------------------------
}

//Subfunction
Struct_viewport* VK_viewport::create_viewport(){
  vec2 win_dim = ele_window->get_window_dim();
  //---------------------------

  //Viewport
  Struct_viewport* viewport = new Struct_viewport();
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
