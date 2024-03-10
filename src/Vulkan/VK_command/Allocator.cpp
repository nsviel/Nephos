#include "Allocator.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Allocator::Allocator(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pool = new vk::instance::Pool(struct_vulkan);

  //---------------------------
}
Allocator::~Allocator(){}

//Main function
void Allocator::init(){
  this->vk_command_buffer = new vk::command::Command_buffer(struct_vulkan);
  //---------------------------

  vk::pool::Command_buffer* pool;
  pool = &struct_vulkan->device.queue.graphics.pool;
  vk_pool->create_command_pool(pool, struct_vulkan->device.queue.graphics.family_ID);
  vk_command_buffer->init_pool(pool);

  pool = &struct_vulkan->device.queue.transfer.pool;
  vk_pool->create_command_pool(pool, struct_vulkan->device.queue.transfer.family_ID);
  vk_command_buffer->init_pool(pool);

  for(int i=0; i<100; i++){
    vk::pool::Command_buffer pool;
    vk_pool->create_command_pool(&pool, struct_vulkan->device.queue.transfer.family_ID);
    vk_command_buffer->init_pool(&pool);

    struct_vulkan->device.queue.transfer.vec_pool.push_back(pool);
  }

  //---------------------------
}
void Allocator::reset(){
  //---------------------------

  vk::pool::Command_buffer* pool;
  pool = &struct_vulkan->device.queue.graphics.pool;
  vk_command_buffer->reset_pool(pool);

  pool = &struct_vulkan->device.queue.transfer.pool;
  vk_command_buffer->reset_pool(pool);

  vector<vk::pool::Command_buffer>& vec_pool = struct_vulkan->device.queue.transfer.vec_pool;
  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::Command_buffer& pool = vec_pool[i];
    vk_command_buffer->reset_pool(&pool);
  }

  //---------------------------
}
void Allocator::clean(){
  //---------------------------

  vk::pool::Command_buffer* pool;
  pool = &struct_vulkan->device.queue.graphics.pool;
  vk_command_buffer->clean_pool(pool);
  vk_pool->clean_command_pool(pool);

  pool = &struct_vulkan->device.queue.transfer.pool;
  vk_command_buffer->clean_pool(pool);
  vk_pool->clean_command_pool(pool);

  vector<vk::pool::Command_buffer>& vec_pool = struct_vulkan->device.queue.transfer.vec_pool;
  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::Command_buffer& pool = vec_pool[i];
    vk_command_buffer->clean_pool(&pool);
    vk_pool->clean_command_pool(&pool);
  }

  //---------------------------
}

}
