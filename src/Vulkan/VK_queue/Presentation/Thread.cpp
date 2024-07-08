#include "Thread.h"

#include <Vulkan/Namespace.h>


namespace vk::queue::presentation{

//Constructor / Destructor
Thread::Thread(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_window = new vk::window::GLFW(vk_struct);
  this->vk_submission = new vk::queue::presentation::Submission(vk_struct);

  //---------------------------
}
Thread::~Thread(){}

//Main function
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

//Subfunction
void Thread::add_command(std::vector<vk::structure::Command*> vec_command){
  //---------------------------

  vk::structure::Command* command = vec_command[vec_command.size() - 1];
  VkSemaphore& semaphore = command->semaphore_done;



  vk_struct->queue.graphics->add_presentation(vec_command);
  //vk_struct->queue.graphics->wait_for_idle();
  //this->image_presentation(semaphore);

  //---------------------------
}

}
