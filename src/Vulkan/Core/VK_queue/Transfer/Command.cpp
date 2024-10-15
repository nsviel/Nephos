#include "Command.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace vk::queue::transfer{

//Constructor / Destructor
Command::Command(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_submission = new vk::queue::transfer::Submission(vk_struct);

  //---------------------------
  this->start_thread();
}
Command::~Command(){}

//Main function
void Command::thread_init(){
  //---------------------------

  vk_struct->core.device.queue.transfer.type = vk::queue::TRANSFER;
  vk_struct->core.device.queue.transfer.thread_ID = thr::get_ID_str();

  //---------------------------
}
void Command::thread_loop(){
  //---------------------------

  //Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this]{return (!queue.empty() && !thread_paused) || !thread_running;});
  if(!thread_running) return;

  //Submit command
  this->state = vk::queue::SUBMIT_COMMAND;
  
  vk_submission->process_command(*queue.front());
  queue.pop();

  //---------------------------
}

//Subfunction
void Command::add_command(std::shared_ptr<vk::structure::Command_buffer> command_buffer){
  mutex.lock();
  //---------------------------

  if(command_buffer->is_recorded){
    queue.push(command_buffer);
    cv.notify_one();
  }

  //---------------------------
  mutex.unlock();
}

}
