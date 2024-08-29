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
  vk_struct->device.queue.transfer.thread_ID = thr::get_ID_str();

  //---------------------------
}
void Thread::thread_loop(){
  //---------------------------

  //Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this]{return (!queue.empty() && !thread_paused) || !thread_running;});
  if(!thread_running) return;

  //Submit command
  vk_submission->process_command(queue.front());
  queue.pop();

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
    cv.notify_one();
  }

  //---------------------------
  mutex.unlock();
}

}
