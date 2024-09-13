#include "Viewport.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Viewport::Viewport(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Viewport::~Viewport(){}

//Main function
void Viewport::init(){
  glm::vec2 win_dim = vk_struct->window.dimension;
  //---------------------------

  //Viewport
  vk_struct->viewport.handle = {};
  vk_struct->viewport.handle.x = 0;
  vk_struct->viewport.handle.y = 0;
  vk_struct->viewport.handle.width  = win_dim.x;
  vk_struct->viewport.handle.height = win_dim.y;
  vk_struct->viewport.handle.minDepth = 0.0f;
  vk_struct->viewport.handle.maxDepth = 1.0f;

  //Full viewport scissor
  vk_struct->viewport.scissor = {};
  vk_struct->viewport.scissor.offset = {0, 0};
  vk_struct->viewport.scissor.extent = vk_struct->window.extent;

  //---------------------------
}
void Viewport::cmd_viewport(VkCommandBuffer& command_buffer){
  //---------------------------

  //Viewport
  vkCmdSetViewport(command_buffer, 0, 1, &vk_struct->viewport.handle);

  //Scissor
  vkCmdSetScissor(command_buffer, 0, 1, &vk_struct->viewport.scissor);

  //---------------------------
}
void Viewport::update_viewport(){
  glm::vec2 win_dim = vk_struct->window.dimension;
  //---------------------------

  //Viewport scene
  vk_struct->viewport.handle.x = 0;
  vk_struct->viewport.handle.y = 0;
  vk_struct->viewport.handle.width  = win_dim.x;
  vk_struct->viewport.handle.height = win_dim.y;

  //Scissor
  vk_struct->viewport.scissor.extent = vk_struct->window.extent;

  //---------------------------
}

//Subfunction
vk::structure::Viewport* Viewport::create_viewport(){
  glm::vec2 win_dim = vk_struct->window.dimension;
  //---------------------------

  //Viewport
  vk::structure::Viewport* viewport = new vk::structure::Viewport();
  viewport->handle = {};
  viewport->handle.x = 0;
  viewport->handle.y = 0;
  viewport->handle.width  = win_dim.x;
  viewport->handle.height = win_dim.y;
  viewport->handle.minDepth = 0.0f;
  viewport->handle.maxDepth = 1.0f;

  //Full viewport scissor
  viewport->scissor = {};
  viewport->scissor.offset = {0, 0};
  viewport->scissor.extent = vk_struct->window.extent;

  //---------------------------
  return viewport;
}

}
