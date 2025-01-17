#include "Command.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::queue::graphics{

//Constructor / Destructor
Command::Command(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_submission = new vk::queue::graphics::Submission(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);

  //---------------------------
  this->start_thread();

}
Command::~Command(){}

//Main function
void Command::thread_init(){
  //---------------------------

  vk_struct->core.device.queue.graphics.type = vk::queue::GRAPHICS;
  vk_struct->core.device.queue.graphics.thread_ID = thr::get_ID_str();

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
    vk_submission->process_command(queue.front());
    queue.pop();
  }

  //---------------------------
}

//Subfunction
void Command::add_command(std::unique_ptr<vk::structure::Command> command){
  //---------------------------

  mutex.lock();

  std::shared_ptr<vk::structure::Command_set> set = std::make_shared<vk::structure::Command_set>();
  set->vec_command.push_back(std::move(command));
  queue.push(set);

  mutex.unlock();
  cv.notify_one();

  //---------------------------
}
void Command::add_command(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  mutex.lock();

  std::shared_ptr<vk::structure::Command_set> set = std::make_shared<vk::structure::Command_set>();
  set->vec_command.push_back(std::move(render->command));
  set->presentation = false;
  set->semaphore = render->semaphore;

  queue.push(set);

  mutex.unlock();
  cv.notify_one();

  set->wait_until_done();

  //---------------------------
}
void Command::add_command(std::shared_ptr<vk::structure::Batch> batch){
  //---------------------------

  mutex.lock();

  std::shared_ptr<vk::structure::Command_set> set = std::make_shared<vk::structure::Command_set>();
  set->vec_command = std::move(batch->vec_command);
  set->presentation = true;
  set->semaphore = batch->semaphore;

  queue.push(set);

  mutex.unlock();
  cv.notify_one();

  set->wait_until_done();

  //---------------------------
}

}
