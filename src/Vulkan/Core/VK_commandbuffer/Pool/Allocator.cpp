#include "Allocator.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::commandbuffer{

//Constructor / Destructor
Allocator::Allocator(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pool = new vk::instance::Pool(vk_struct);

  //---------------------------
}
Allocator::~Allocator(){}

//Main function
void Allocator::init(){
  this->vk_command_buffer = new vk::commandbuffer::Pool(vk_struct);
  //---------------------------

  this->create_command_buffer_pool(vk_struct->core.device.queue.graphics);
  this->create_command_buffer_pool(vk_struct->core.device.queue.transfer);

  //---------------------------
}
void Allocator::reset(){
  //---------------------------

  this->reset_command_buffer_pool(vk_struct->core.device.queue.graphics);
  this->reset_command_buffer_pool(vk_struct->core.device.queue.transfer);

  //---------------------------
}
void Allocator::clean(){
  //---------------------------

  this->clean_command_buffer_pool(vk_struct->core.device.queue.graphics);
  this->clean_command_buffer_pool(vk_struct->core.device.queue.transfer);

  //---------------------------
}

//Subfunction
void Allocator::create_command_buffer_pool(vk::structure::Queue& queue){
  //---------------------------

  //Number of command buffer pool
  int number = vk_struct->core.device.physical_device.discrete_gpu ? 100 : 10;

  //Create a pool of command buffer pool number
  for(int i=0; i<number; i++){
    vk::pool::structure::Command_buffer* pool = new vk::pool::structure::Command_buffer();
    vk_pool->create_command_pool(pool, queue.family_ID);
    vk_command_buffer->init_pool(pool);

    queue.vec_pool.push_back(pool);
  }

  //---------------------------
}
void Allocator::reset_command_buffer_pool(vk::structure::Queue& queue){
  //---------------------------

  for(auto& pool : queue.vec_pool){
    vk_command_buffer->reset_pool(pool);
  }

  //---------------------------
}
void Allocator::clean_command_buffer_pool(vk::structure::Queue& queue){
  //---------------------------

  for(auto& pool : queue.vec_pool){
    vk_command_buffer->clean_pool(pool);
    vk_pool->clean_command_pool(pool);
  }

  //---------------------------
}

//Command buffer pool use
vk::pool::structure::Command_buffer* Allocator::query_free_pool(vk::structure::Queue& queue){
  std::thread::id this_thread_ID = thr::get_ID();
  //---------------------------

  //Return pool associated with thread ID
  for(auto& pool : queue.vec_pool){
    if(pool->is_available == false && pool->thread_ID == this_thread_ID){
      return pool;
    }
  }

  //Else give it a specific pool
  for(auto& pool : queue.vec_pool){
    std::lock_guard<std::mutex> lock(pool->mutex);
    if(pool->is_available){
      pool->is_available = false;
      pool->thread_ID = this_thread_ID;
      return pool;
    }
  }

  std::cout<<"[error] Command buffer pool availbility problem"<<std::endl;

  //---------------------------
  return nullptr;
}

}
