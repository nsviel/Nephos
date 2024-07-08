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

  //Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this] { return (!queue.empty() && !pause) || !thread_running;});

  //Submit command
  vk_submission->process_command(queue.front(), with_presentation);
  queue.pop();

  //---------------------------
}
void Thread::thread_pause(bool value){
  //---------------------------

  this->pause = value;
  cv.notify_one();

  //---------------------------
}

//Subfunction
void Thread::add_command(vk::structure::Command* command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  mutex.lock();
  this->with_presentation = false;
  std::vector<vk::structure::Command*> vec_command;
  vec_command.push_back(command);
  queue.push(vec_command);

  mutex.unlock();
  cv.notify_one();

  //---------------------------
}
void Thread::add_graphics(std::vector<vk::structure::Command*> vec_command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  mutex.lock();
  this->with_presentation = false;
  queue.push(vec_command);
  mutex.unlock();
  cv.notify_one();

  //---------------------------

}
void Thread::add_presentation(std::vector<vk::structure::Command*> vec_command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  mutex.lock();
  this->with_presentation = true;
  queue.push(vec_command);
  mutex.unlock();
  cv.notify_one();

  //---------------------------
}


}
