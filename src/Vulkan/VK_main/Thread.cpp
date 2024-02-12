#include "Thread.h"

#include <Vulkan/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Thread::Thread(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pool = new vk::instance::Pool(struct_vulkan);

  //---------------------------
}
Thread::~Thread(){}

//Main function
void Thread::init(){
  this->vk_command_buffer = new vk::command::Command_buffer(struct_vulkan);
  //---------------------------

  vk::pool::Thread* pool = &struct_vulkan->pools.thread;

  vk::pool::Command_buffer command_pool;
  vk_pool->create_command_pool(&command_pool);
  vk_command_buffer->init_pool(&command_pool);
  pool->tank.push_back(command_pool);


/*
  //Secondary threads
  vk::pool::Thread* pool = &struct_vulkan->pools.thread;
  for(int i=0; i<pool->size; i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];


  }
*/
  //---------------------------
}
void Thread::reset(){
  vk::pool::Thread* pool = &struct_vulkan->pools.thread;
  //---------------------------

  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];
    vk_command_buffer->reset_pool(command_pool);
  }

  //---------------------------
}
void Thread::submit_commands(){
  vk::pool::Thread* pool = &struct_vulkan->pools.thread;
  //---------------------------

  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];
    vk_command_buffer->submit_pool(command_pool);
    vk_command_buffer->reset_pool(command_pool);
  }

  //---------------------------
}
void Thread::clean(){
  vk::pool::Thread* pool = &struct_vulkan->pools.thread;
  //---------------------------

  for(int i=0; i<pool->tank.size(); i++){
    vk::pool::Command_buffer* command_pool = &pool->tank[i];
    vk_command_buffer->clean_pool(command_pool);
    vk_pool->clean_command_pool(command_pool);
  }

  //---------------------------
}

//Subfunction
vk::pool::Command_buffer* Thread::query_command_pool(int ID){
  vk::pool::Command_buffer* command_pool = nullptr;
  //---------------------------

  vk::pool::Thread* pool = &struct_vulkan->pools.thread;
  command_pool = &pool->tank[0];

  //---------------------------
  return command_pool;
}

}
