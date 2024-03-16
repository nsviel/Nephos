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

  this->create_command_buffer_pool(&struct_vulkan->device.queue.graphics);
  this->create_command_buffer_pool(&struct_vulkan->device.queue.transfer);

  //---------------------------
}
void Allocator::reset(){
  //---------------------------

  this->reset_command_buffer_pool(&struct_vulkan->device.queue.graphics);
  this->reset_command_buffer_pool(&struct_vulkan->device.queue.transfer);

  //---------------------------
}
void Allocator::clean(){
  //---------------------------

  this->clean_command_buffer_pool(&struct_vulkan->device.queue.graphics);
  this->clean_command_buffer_pool(&struct_vulkan->device.queue.transfer);

  //---------------------------
}

//Subfunction
void Allocator::create_command_buffer_pool(vk::structure::Queue* queue){
  //---------------------------

  //Number of command buffer pool
  int number = struct_vulkan->device.physical_device.discrete_gpu ? 100 : 10;

  //Create a pool of command buffer pool number
  for(int i=0; i<number; i++){
    vk::pool::Command_buffer pool;
    vk_pool->create_command_pool(&pool, queue->family_ID);
    vk_command_buffer->init_pool(&pool);

    queue->vec_pool.push_back(pool);
  }

  //---------------------------
}
void Allocator::reset_command_buffer_pool(vk::structure::Queue* queue){
  vector<vk::pool::Command_buffer>& vec_pool = queue->vec_pool;
  //---------------------------

  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::Command_buffer& pool = vec_pool[i];
    vk_command_buffer->reset_pool(&pool);
  }

  //---------------------------
}
void Allocator::clean_command_buffer_pool(vk::structure::Queue* queue){
  vector<vk::pool::Command_buffer>& vec_pool = queue->vec_pool;
  //---------------------------

  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::Command_buffer& pool = vec_pool[i];
    vk_command_buffer->clean_pool(&pool);
    vk_pool->clean_command_pool(&pool);
  }

  //---------------------------
}

//Command buffer pool use
vk::pool::Command_buffer* Allocator::query_free_pool(vk::structure::Queue* queue){
  vector<vk::pool::Command_buffer>& vec_pool = queue->vec_pool;
  std::thread::id this_thread_ID = std::this_thread::get_id();
  //---------------------------

  //Return pool associated with thread ID
  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::Command_buffer* pool = &vec_pool[i];

    if(pool->is_available == false && pool->thread_ID == this_thread_ID){
      return pool;
    }
  }

  //Else give it a specific pool
  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::Command_buffer* pool = &vec_pool[i];

    if(pool->is_available){
      pool->is_available = false;
      pool->thread_ID = this_thread_ID;
      return pool;
    }
  }

  cout<<"[error] Command buffer pool availbility problem"<<endl;

  //---------------------------
  return nullptr;
}

}
