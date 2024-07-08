#include "Thread.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::queue::presentation{

//Constructor / Destructor
Thread::Thread(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_window = new vk::window::GLFW(vk_struct);
  this->vk_submission = new vk::queue::presentation::Submission(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);

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
  //vk_submission->process_command(queue.front());
  //queue.pop();

  //---------------------------
}

//Subfunction
void Thread::add_command(vk::command::structure::Set* set){
  //---------------------------

  set->supress = false;
  vk_struct->queue.graphics->add_command(set);
  set->wait_until_done();
  vk_submission->process_command(set->semaphore);
  delete set;

  //queue.push(set);

  //---------------------------
}

}
