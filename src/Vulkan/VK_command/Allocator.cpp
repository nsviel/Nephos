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
void Allocator::reset(){
  vk::pool::Command* pool = &struct_vulkan->pools.command;
  //---------------------------

  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];
    vk_command_buffer->reset_pool(command_pool);
  }

  //---------------------------
}
void Allocator::submit_commands(){
  vk::pool::Command* pool = &struct_vulkan->pools.command;
  //---------------------------
/*
  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];
    vk_command_buffer->submit_pool(command_pool);
    vk_command_buffer->reset_pool(command_pool);
  }
  */

  //Submit man thread commands
  vk::pool::Command_buffer* command_pool = &pool->tank[0];
  vk_command_buffer->submit_pool(command_pool);
  vk_command_buffer->reset_pool(command_pool);

  //---------------------------
}
void Allocator::clean(){
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
vk::pool::Command_buffer* Allocator::query_free_command_pool(){
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
