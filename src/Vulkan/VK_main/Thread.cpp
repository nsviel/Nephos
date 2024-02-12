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
  //---------------------------
  this->vk_command_buffer = new vk::command::Command_buffer(struct_vulkan);

  //Main thread command buffer pool
  THREAD_ID thread_ID = std::this_thread::get_id();
  struct_vulkan->pools.command_buffer[thread_ID] = vk::pool::Command_buffer();

  vk::pool::Command_buffer* pool = query_current_command_pool();
  vk_pool->create_command_pool(pool);
  vk_command_buffer->init_pool(pool);

  //---------------------------
}
void Thread::reset(){
  //---------------------------

  for(auto& pair : struct_vulkan->pools.command_buffer){
    vk::pool::Command_buffer* pool = &pair.second;
    vk_command_buffer->reset_pool(pool);
  }

  //---------------------------
}
void Thread::submit_commands(){
  //---------------------------

  for(auto& pair : struct_vulkan->pools.command_buffer){
    vk::pool::Command_buffer* pool = &pair.second;
    vk_command_buffer->submit_pool(pool);
    vk_command_buffer->reset_pool(pool);
  }

  //---------------------------
}
void Thread::clean(){
  //---------------------------

  for(auto& pair : struct_vulkan->pools.command_buffer){
    vk::pool::Command_buffer* pool = &pair.second;
    vk_command_buffer->clean_pool(pool);
    vk_pool->clean_command_pool(pool);
  }

  //---------------------------
}

//Subfunction
void Thread::create_thread_command_pool(){
  //---------------------------

  //Main thread command buffer pool
  THREAD_ID thread_ID = std::this_thread::get_id();
  struct_vulkan->pools.command_buffer[thread_ID] = vk::pool::Command_buffer();

  vk::pool::Command_buffer* pool = query_current_command_pool();
  vk_pool->create_command_pool(pool);
  vk_command_buffer->init_pool(pool);

  //---------------------------
}
vk::pool::Command_buffer* Thread::query_current_command_pool(){
  //---------------------------

  THREAD_ID thread_ID = std::this_thread::get_id();
  vk::pool::Command_buffer* pool = &struct_vulkan->pools.command_buffer[thread_ID];

  //---------------------------
  return pool;
}

}
