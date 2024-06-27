#include "Allocator.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

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
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  //---------------------------

  this->create_command_buffer_pool(&vk_struct->device.queue.graphics);
  this->create_command_buffer_pool(&vk_struct->device.queue.transfer);

  //---------------------------
}
void Allocator::reset(){
  //---------------------------

  this->reset_command_buffer_pool(&vk_struct->device.queue.graphics);
  this->reset_command_buffer_pool(&vk_struct->device.queue.transfer);

  //---------------------------
}
void Allocator::clean(){
  //---------------------------

  this->clean_command_buffer_pool(&vk_struct->device.queue.graphics);
  this->clean_command_buffer_pool(&vk_struct->device.queue.transfer);

  //---------------------------
}

//Subfunction
void Allocator::create_command_buffer_pool(vk::queue::structure::Queue* queue){
  //---------------------------

  //Number of command buffer pool
  int number = vk_struct->device.physical_device.discrete_gpu ? 100 : 10;

  //Create a pool of command buffer pool number
  for(int i=0; i<number; i++){
    vk::pool::structure::Command_buffer* pool = new vk::pool::structure::Command_buffer();
    vk_pool->create_command_pool(pool, queue->family_ID);
    vk_command_buffer->init_pool(pool);

    queue->vec_pool.push_back(pool);
  }

  //---------------------------
}
void Allocator::reset_command_buffer_pool(vk::queue::structure::Queue* queue){
  vector<vk::pool::structure::Command_buffer*>& vec_pool = queue->vec_pool;
  //---------------------------

  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::structure::Command_buffer* pool = vec_pool[i];
    vk_command_buffer->reset_pool(pool);
  }

  //---------------------------
}
void Allocator::clean_command_buffer_pool(vk::queue::structure::Queue* queue){
  vector<vk::pool::structure::Command_buffer*>& vec_pool = queue->vec_pool;
  //---------------------------

  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::structure::Command_buffer* pool = vec_pool[i];
    vk_command_buffer->clean_pool(pool);
    vk_pool->clean_command_pool(pool);
  }

  //---------------------------
}

//Command buffer pool use
vk::pool::structure::Command_buffer* Allocator::query_free_pool(vk::queue::structure::Queue* queue){
  vector<vk::pool::structure::Command_buffer*>& vec_pool = queue->vec_pool;
  std::thread::id this_thread_ID = utl::thread::get_ID();
  //---------------------------

  //Return pool associated with thread ID
  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::structure::Command_buffer* pool = vec_pool[i];

    if(pool->is_available == false && pool->thread_ID == this_thread_ID){
      return pool;
    }
  }

  //Else give it a specific pool
  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::structure::Command_buffer* pool = vec_pool[i];

    std::lock_guard<std::mutex> lock(pool->mutex);
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
