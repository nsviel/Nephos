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
vk::pool::Command_buffer* Thread::query_free_command_pool(){
  vk::pool::Thread* pool = &struct_vulkan->pools.thread;
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
