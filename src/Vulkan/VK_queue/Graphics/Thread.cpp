#include "Thread.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::queue::graphics{

//Constructor / Destructor
Thread::Thread(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_query = new vk::instance::Query(vk_struct);
  this->vk_submission = new vk::queue::graphics::Submission(vk_struct);

  //---------------------------
  this->start_thread();

}
Thread::~Thread(){}

//Main function
void Thread::thread_init(){
  //---------------------------

  vk_struct->device.queue.graphics.type = vk::queue::GRAPHICS;
  vk_struct->device.queue.graphics.thread_ID = utl::thread::get_ID_str();
  vk_struct->device.queue.presentation.type = vk::queue::PRESENTATION;
  vk_struct->device.queue.presentation.thread_ID = utl::thread::get_ID_str();

  //---------------------------
}
void Thread::thread_loop(){
  //---------------------------

  this->wait_for_command();

  //Passing the command torch
  mutex.lock();
  this->vec_command_onrun = vec_command_prepa;
  this->vec_command_prepa.clear();
  mutex.unlock();

  this->thread_idle = false;
  vk_submission->process_command(vec_command_onrun, with_presentation);
  this->thread_idle = true;

  //---------------------------
}

//Subfunction
void Thread::add_command(vk::structure::Command* command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  this->wait_for_idle();

  mutex.lock();
  this->thread_idle = false;
  this->with_presentation = false;
  vec_command_prepa.push_back(command);
  mutex.unlock();

  //---------------------------
}
void Thread::add_graphics(std::vector<vk::structure::Command*> vec_command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  this->wait_for_idle();

  mutex.lock();
  this->thread_idle = false;
  this->with_presentation = false;
  vec_command_prepa = vec_command;
  mutex.unlock();

  //---------------------------

}
void Thread::add_presentation(std::vector<vk::structure::Command*> vec_command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  this->wait_for_idle();

  mutex.lock();
  this->thread_idle = false;
  this->with_presentation = true;
  vec_command_prepa = vec_command;
  mutex.unlock();

  //---------------------------
}
void Thread::wait_for_command(){
  //For internal thread to wait for to submit commands
  //---------------------------

  while((vec_command_prepa.empty()) && thread_running){
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
