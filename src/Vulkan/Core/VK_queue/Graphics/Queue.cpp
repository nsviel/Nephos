#include "Queue.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::queue::graphics{

//Constructor / Destructor
Queue::Queue(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_submission = new vk::queue::graphics::Submission(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);

  //---------------------------
  this->start_thread();

}
Queue::~Queue(){}

//Main function
void Queue::thread_init(){
  //---------------------------

  vk_struct->core.device.queue.graphics.type = vk::queue::GRAPHICS;
  vk_struct->core.device.queue.graphics.thread_ID = thr::get_ID_str();

  //---------------------------
}
void Queue::thread_loop(){
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
void Queue::add_command(std::unique_ptr<vk::structure::Command> command){
  if(vk_struct->core.queue.standby) return;
  //---------------------------

  mutex.lock();

  vk::command::structure::Set* set = new vk::command::structure::Set();
  set->vec_command.push_back(std::move(command));
  queue.push(set);

  mutex.unlock();
  cv.notify_one();

  //---------------------------
}
void Queue::add_command(std::vector<std::unique_ptr<vk::structure::Command>> vec_command){
  if(vk_struct->core.queue.standby) return;
  //---------------------------

  mutex.lock();

  vk::command::structure::Set* set = new vk::command::structure::Set();
  set->vec_command = std::move(vec_command);;
  queue.push(set);

  mutex.unlock();
  cv.notify_one();

  //---------------------------
}
void Queue::add_command(vk::command::structure::Set* set){
  if(vk_struct->core.queue.standby) return;
  //---------------------------

  mutex.lock();

  queue.push(set);

  mutex.unlock();
  cv.notify_one();

  //---------------------------
}

}
