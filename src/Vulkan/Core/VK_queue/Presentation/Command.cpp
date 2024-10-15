#include "Command.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::queue::presentation{

//Constructor / Destructor
Command::Command(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::draw::Renderer(vk_struct);
  this->vk_submission = new vk::queue::presentation::Submission(vk_struct);

  //---------------------------
  this->start_thread();
}
Command::~Command(){}

//Main function
void Command::thread_init(){
  //---------------------------

  vk_struct->core.device.queue.presentation.type = vk::queue::PRESENTATION;
  vk_struct->core.device.queue.presentation.thread_ID = thr::get_ID_str();

  //---------------------------
}
void Command::thread_loop(){
  //---------------------------

  //Wait for command
  std::unique_lock<std::mutex> lock(mutex);
  cv.wait(lock, [this]{return !queue.empty() || !thread_running;});

  //Submit command
  if(queue.size() > 0){
    this->state = vk::queue::SUBMIT_COMMAND;
    vk_submission->submit_presentation(queue.front());
    queue.pop();
  }

  //---------------------------
}

//Subfunction
void Command::add_command(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  mutex.lock();
  queue.push(render);
  mutex.unlock();
  cv.notify_one();

  //---------------------------
}

}
