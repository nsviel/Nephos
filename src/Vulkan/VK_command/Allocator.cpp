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

  //Graphics queue pool
  for(int i=0; i<100; i++){
    vk::pool::Command_buffer pool;
    vk_pool->create_command_pool(&pool, struct_vulkan->device.queue.graphics.family_ID);
    vk_command_buffer->init_pool(&pool);

    struct_vulkan->device.queue.graphics.vec_pool.push_back(pool);
  }

  //Transfer queue pool
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

  //Graphics queue pool
  {
    vector<vk::pool::Command_buffer>& vec_pool = struct_vulkan->device.queue.graphics.vec_pool;
    for(int i=0; i<vec_pool.size(); i++){
      vk::pool::Command_buffer& pool = vec_pool[i];
      vk_command_buffer->reset_pool(&pool);
    }
  }


  //Transfer queue pool
  vector<vk::pool::Command_buffer>& vec_pool = struct_vulkan->device.queue.transfer.vec_pool;
  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::Command_buffer& pool = vec_pool[i];
    vk_command_buffer->reset_pool(&pool);
  }

  //---------------------------
}
void Allocator::clean(){
  //---------------------------

  //Graphics queue pool
  {
    vector<vk::pool::Command_buffer>& vec_pool = struct_vulkan->device.queue.graphics.vec_pool;
    for(int i=0; i<vec_pool.size(); i++){
      vk::pool::Command_buffer& pool = vec_pool[i];
      vk_command_buffer->clean_pool(&pool);
      vk_pool->clean_command_pool(&pool);
    }
  }


  //Transfer queue pool
  vector<vk::pool::Command_buffer>& vec_pool = struct_vulkan->device.queue.transfer.vec_pool;
  for(int i=0; i<vec_pool.size(); i++){
    vk::pool::Command_buffer& pool = vec_pool[i];
    vk_command_buffer->clean_pool(&pool);
    vk_pool->clean_command_pool(&pool);
  }

  //---------------------------
}

//Subfunction
vk::pool::Command_buffer* Allocator::query_free_pool(vk::structure::Queue* queue){
  vector<vk::pool::Command_buffer>& vec_pool = queue->vec_pool;
  //---------------------------

  // Random number generator setup
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(0, vec_pool.size() - 1);

  // Find a random available and unrecorded command buffer
  int index;
  vk::pool::Command_buffer* pool;
  do{
    index = distr(gen);
    pool = &vec_pool[index];

    if(pool->is_available){
      pool->is_available = false;
      return pool;
    }
  }while(true);

  cout<<"[error] Command buffer pool availbility problem"<<endl;

  //---------------------------
  return nullptr;
}
void Allocator::free_pool(vk::pool::Command_buffer* pool){
  //---------------------------

  pool->is_available = true;

  //---------------------------
}

}
