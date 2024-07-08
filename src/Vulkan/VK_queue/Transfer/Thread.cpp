#include "Thread.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace vk::queue::transfer{

//Constructor / Destructor
Thread::Thread(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_submission = new vk::queue::transfer::Submission(vk_struct);

  //---------------------------
  this->start_thread();
}
Thread::~Thread(){}

//Main function
void Thread::thread_init(){
  //---------------------------

  vk_struct->device.queue.transfer.type = vk::queue::TRANSFER;
  vk_struct->device.queue.transfer.thread_ID = utl::thread::get_ID_str();

  //---------------------------
}
void Thread::thread_loop(){
  //---------------------------

  this->wait_for_command();

  this->thread_idle = false;
  vk_submission->process_command(queue.front());
  queue.pop();
  this->thread_idle = true;

  //---------------------------
}

//Subfunction
void Thread::add_command(vk::structure::Command_buffer* command){
  mutex.lock();
  //---------------------------

  if(command->is_recorded){
    std::vector<vk::structure::Command_buffer*> vec_command;
    vec_command.push_back(command);
    queue.push(vec_command);
  }

  //---------------------------
  mutex.unlock();
}
void Thread::wait_for_command(){
  //For internal thread to wait for to submit commands
  //---------------------------

  while((queue.empty() || vk_struct->queue.standby) && thread_running){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Thread::wait_for_idle(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

}
