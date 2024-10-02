#include "Command_buffer.h"

#include <Vulkan/Namespace.h>
#include <random>


namespace vk::commandbuffer{

//Constructor / Destructor
Command_buffer::Command_buffer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_allocator = new vk::commandbuffer::Allocator(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_query = new vk::instance::Query(vk_struct);

  //---------------------------
}
Command_buffer::~Command_buffer(){}

//Main function
void Command_buffer::init_pool(vk::pool::structure::Command_buffer* pool){
  //---------------------------

  //Number of command buffer
  int number = vk_struct->core.device.physical_device.discrete_gpu ? 100 : 10;
  pool->size = number;

  //Create a pool of command buffer number
  for(int i=0; i<number; i++){
    //Create command buffer struct pointer
    std::shared_ptr<vk::structure::Command_buffer> command_buffer = std::make_shared<vk::structure::Command_buffer>();
    command_buffer->is_available = true;
    command_buffer->is_recorded = false;
    command_buffer->UID = vk_uid->query_free_UID();
    command_buffer->query = vk_query->create_query_pool();

    //Instanciate it and insert in tank
    this->create_command_buffer_primary(pool, *command_buffer);
    pool->tank.push_back(command_buffer);
  }

  //---------------------------
}
void Command_buffer::reset_pool(vk::pool::structure::Command_buffer* pool){
  //---------------------------

  //Clear all old command buffer
  for(auto& command_buffer : pool->tank){
    if(command_buffer->is_resetable){
      command_buffer->is_available = true;
      command_buffer->is_recorded = false;
    }
  }

  //---------------------------
}
void Command_buffer::clean_pool(vk::pool::structure::Command_buffer* pool){
  //---------------------------

  //Clear all old command buffer
  for(auto& command_buffer : pool->tank){
    vk_query->clean_query_pool(&command_buffer->query);
    vkFreeCommandBuffers(vk_struct->core.device.handle, pool->allocator, 1, &command_buffer->handle);
  }

  //---------------------------
}

//Subfunction
void Command_buffer::create_command_buffer_primary(vk::pool::structure::Command_buffer* pool, vk::structure::Command_buffer& command_buffer){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandPool = pool->allocator;
  alloc_info.commandBufferCount = 1;

  VkResult result = vkAllocateCommandBuffers(vk_struct->core.device.handle, &alloc_info, &command_buffer.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
void Command_buffer::create_command_buffer_secondary(vk::structure::Object* data){
  vk::pool::structure::Command_buffer* pool = vk_allocator->query_free_pool(vk_struct->core.device.queue.transfer);
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
  alloc_info.commandPool = pool->allocator;
  alloc_info.commandBufferCount = 1;

  VkResult result = vkAllocateCommandBuffers(vk_struct->core.device.handle, &alloc_info, &data->command_buffer_secondary);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}

}
