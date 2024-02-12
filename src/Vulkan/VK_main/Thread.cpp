#include "Thread.h"

#include <Vulkan/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Thread::Thread(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Thread::~Thread(){}

//Main function
void Thread::init(){
  //---------------------------

  //Main thread command buffer pool
  THREAD_ID thread_ID = std::this_thread::get_id();
  struct_vulkan->pools.command_buffer[thread_ID] = vk::pool::Command_buffer();

  //---------------------------
}

//Subfunction
vk::pool::Command_buffer* Thread::query_current_command_pool(){
  //---------------------------

  THREAD_ID thread_ID = std::this_thread::get_id();
  vk::pool::Command_buffer* pool = &struct_vulkan->pools.command_buffer[thread_ID];

  //---------------------------
  return pool;
}

}
