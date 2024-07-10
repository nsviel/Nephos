#include "Thread.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::queue::presentation{

//Constructor / Destructor
Thread::Thread(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_submission = new vk::queue::presentation::Submission(vk_struct);

  //---------------------------
  this->start_thread();
}
Thread::~Thread(){}

//Main function
void Thread::thread_init(){
  //---------------------------

  vk_struct->device.queue.presentation.type = vk::queue::PRESENTATION;
  vk_struct->device.queue.presentation.thread_ID = utl::thread::get_ID_str();

  //---------------------------
}
void Thread::thread_loop(){
  //---------------------------

  //Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this]{return (!queue.empty() && !thread_paused) || !thread_running;});
  if(!thread_running) return;

  //Submit command
  vk_submission->process_command();
  queue.pop();

  //---------------------------
}

//Subfunction
void Thread::add_command(){
  //---------------------------

  mutex.lock();
  queue.push(true);
  mutex.unlock();
  cv.notify_one();

  //---------------------------
}

}
