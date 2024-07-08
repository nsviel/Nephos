#include "Thread.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::queue::graphics{

//Constructor / Destructor
Thread::Thread(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
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

  //---------------------------
}
void Thread::thread_loop(){
  //---------------------------

  //Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this]{return (!queue.empty() && !thread_paused) || !thread_running;});
  if(!thread_running) return;

  //Submit command
  vk_submission->process_command(queue.front(), with_presentation);
  queue.pop();

  //---------------------------
}

//Subfunction
void Thread::add_command(vk::structure::Command* command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  mutex.lock();

  this->with_presentation = false;
  vk::command::structure::Set set;
  set.vec_command.push_back(command);
  queue.push(set);

  mutex.unlock();
  cv.notify_one();

  //---------------------------
}
void Thread::add_command(std::vector<vk::structure::Command*> vec_command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  mutex.lock();

  this->with_presentation = false;
  vk::command::structure::Set set;
  set.vec_command = vec_command;
  queue.push(set);

  mutex.unlock();
  cv.notify_one();

  //---------------------------

}
void Thread::add_presentation(std::vector<vk::structure::Command*> vec_command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  mutex.lock();

  this->with_presentation = true;
  vk::command::structure::Set set;
  set.vec_command = vec_command;
  queue.push(set);

  mutex.unlock();
  cv.notify_one();

  //---------------------------
}


}
