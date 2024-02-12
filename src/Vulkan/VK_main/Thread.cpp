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

  struct_vulkan->pools.command_buffer["main"] = vk::pool::Command_buffer();

  //---------------------------
}
vk::pool::Command_buffer* Thread::query_current_command_pool(){
  //---------------------------

  THREAD_ID thread_ID = std::this_thread::get_id();
  vk::pool::Command_buffer* pool = &struct_vulkan->pools.command_buffer["main"];

  //---------------------------
  return pool;
}

}
