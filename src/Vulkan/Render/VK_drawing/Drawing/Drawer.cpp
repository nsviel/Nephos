#include "Drawer.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Drawer::Drawer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_render = new vk::draw::Renderer(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);

  //---------------------------
}
Drawer::~Drawer(){}

//Draw command
void Drawer::cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Object& vk_object){
  //---------------------------

  VkDeviceSize offsets[] = {0};
  if(vk_object.buffer.xyz.data.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(command_buffer, vk::attribut::binding::XYZ, 1, &vk_object.buffer.xyz.data.vbo, offsets);
  }
  if(vk_object.buffer.rgba.data.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(command_buffer, vk::attribut::binding::RGBA, 1, &vk_object.buffer.rgba.data.vbo, offsets);
  }
  if(vk_object.buffer.uv.data.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(command_buffer, vk::attribut::binding::UV, 1, &vk_object.buffer.uv.data.vbo, offsets);
  }

  vkCmdDraw(command_buffer, vk_object.data->xyz.size(), 1, 0, 0);

  //---------------------------
}
void Drawer::cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object& vk_object){
  //---------------------------

  vkCmdSetLineWidth(command_buffer, vk_object.data->width);

  //---------------------------
}

}