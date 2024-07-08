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
void Thread::wait_for_idle(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Thread::image_presentation(VkSemaphore& semaphore){
  this->thread_idle = false;
  //---------------------------

  vk_submission->process_command(semaphore);

  //---------------------------
  this->thread_idle = true;
}
void Thread::add_command(std::vector<vk::structure::Command*> vec_command){
  //---------------------------


  vk::command::structure::Set* set = new vk::command::structure::Set();
  set->vec_command = vec_command;
  set->fence = vk_fence->query_free_fence();
  set->supress = false;


  vk_struct->queue.graphics->add_command(set);

  VkSemaphore semaphore;
  for(int i=0; i<vec_command.size(); i++){
    vk::structure::Command* command = vec_command[i];

    //Semaphore done
    if(command->semaphore_done != VK_NULL_HANDLE){
      semaphore = command->semaphore_done;
    }
  }

  while(set->done == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //delete set;


  //vk_struct->queue.presentation->image_presentation(semaphore);
  //vk_struct->queue.graphics->wait_for_idle();
  //this->image_presentation(semaphore);

  //---------------------------
}

}
