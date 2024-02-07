#include "Command_buffer.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Command_buffer::Command_buffer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_submit = new vk::command::Submit(struct_vulkan);

  //---------------------------
}
Command_buffer::~Command_buffer(){}

//Main function
void Command_buffer::add_command_buffer(VkCommandBuffer& command_buffer){
  std::vector<VkCommandBuffer>& vec_command_buffer = struct_vulkan->command.vec_command_buffer;
  //---------------------------

  vec_command_buffer.push_back(command_buffer);

  //---------------------------
}
void Command_buffer::reset_all_command_buffer(){
  std::vector<VkCommandBuffer>& vec_command_buffer = struct_vulkan->command.vec_command_buffer;
  //---------------------------

  //Clear all old command buffer
  for(int i=0; i<vec_command_buffer.size(); i++){
    VkCommandBuffer& command_buffer = vec_command_buffer[i];

    vkFreeCommandBuffers(struct_vulkan->device.device, struct_vulkan->pool.command, 1, &command_buffer);
    struct_vulkan->pool.nb_command_buffer--;
  }

  //Clear command buffer vector
  struct_vulkan->command.vec_command_buffer.clear();

  //---------------------------
}

}
