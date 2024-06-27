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
  vec2 win_dim = vk_struct->window.dimension;
  //---------------------------

  //Viewport
  vk_struct->render.viewport = {};
  vk_struct->render.viewport.x = 0;
  vk_struct->render.viewport.y = 0;
  vk_struct->render.viewport.width  = win_dim.x;
  vk_struct->render.viewport.height = win_dim.y;
  vk_struct->render.viewport.minDepth = 0.0f;
  vk_struct->render.viewport.maxDepth = 1.0f;

  //Full viewport scissor
  vk_struct->render.scissor = {};
  vk_struct->render.scissor.offset = {0, 0};
  vk_struct->render.scissor.extent = vk_struct->window.extent;

  //---------------------------
}
void Viewport::cmd_viewport(VkCommandBuffer& command_buffer){
  //---------------------------

  //Viewport
  vkCmdSetViewport(command_buffer, 0, 1, &vk_struct->render.viewport);

  //Scissor
  vkCmdSetScissor(command_buffer, 0, 1, &vk_struct->render.scissor);

  //---------------------------
}
void Viewport::update_viewport(){
  vec2 win_dim = vk_struct->window.dimension;
  //---------------------------

  //Viewport scene
  vk_struct->render.viewport.x = 0;
  vk_struct->render.viewport.y = 0;
  vk_struct->render.viewport.width  = win_dim.x;
  vk_struct->render.viewport.height = win_dim.y;

  //Scissor
  vk_struct->render.scissor.extent = vk_struct->window.extent;

  //---------------------------
}

//Subfunction
vk::structure::Viewport* Viewport::create_viewport(){
  vec2 win_dim = vk_struct->window.dimension;
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
  viewport->scissor.extent = vk_struct->window.extent;

  //---------------------------
  return viewport;
}

}
