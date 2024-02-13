#include "Command_allocator.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Command_allocator::Command_allocator(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pool = new vk::instance::Pool(struct_vulkan);

  //---------------------------
}
Command_allocator::~Command_allocator(){}

//Main function
void Command_allocator::init(){
  this->vk_command_buffer = new vk::command::Command_buffer(struct_vulkan);
  //---------------------------

  vk::pool::Command* pool = &struct_vulkan->pools.command;

  for(int i=0; i<pool->size; i++){
    vk::pool::Command_buffer command_pool;
    command_pool.is_available = (i == 0) ? false : true;
    command_pool.thread_ID = (i == 0) ? std::this_thread::get_id() : std::thread::id();

    vk_pool->create_command_pool(&command_pool);
    vk_command_buffer->init_pool(&command_pool);

    pool->tank.push_back(command_pool);
  }

  //---------------------------
}
void Command_allocator::reset(){
  vk::pool::Command* pool = &struct_vulkan->pools.command;
  //---------------------------

  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];
    vk_command_buffer->reset_pool(command_pool);
  }

  //---------------------------
}
void Command_allocator::submit_commands(){
  vk::pool::Command* pool = &struct_vulkan->pools.command;
  //---------------------------

  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];
    vk_command_buffer->submit_pool(command_pool);
    vk_command_buffer->reset_pool(command_pool);
  }

  //---------------------------
}
void Command_allocator::clean(){
  vk::pool::Command* pool = &struct_vulkan->pools.command;
  //---------------------------

  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];
    vk_command_buffer->clean_pool(command_pool);
    vk_pool->clean_command_pool(command_pool);
  }

  //---------------------------
}

//Subfunction
vk::pool::Command_buffer* Command_allocator::query_free_command_pool(){
  vk::pool::Command* pool = &struct_vulkan->pools.command;
  //---------------------------

  //Check if current thread has already an associate command poop
  std::thread::id thread_ID = std::this_thread::get_id();
  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];

    if(thread_ID == command_pool->thread_ID){
      return command_pool;
    }
  }

  //Else send a new one
  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];

    if(command_pool->thread_ID == std::thread::id()){
      command_pool->thread_ID = std::this_thread::get_id();
      return command_pool;
    }
  }

  //Error message
  cout<<"[error] not enough free command pool"<<endl;

  //---------------------------
  return nullptr;
}

}
