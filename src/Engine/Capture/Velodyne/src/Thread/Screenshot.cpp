#include "Screenshot.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Velodyne/Namespace.h>


namespace vld::thread{

//Constructor / Destructor
Screenshot::Screenshot(vld::Node* node_vld){
  //---------------------------

  eng::Node* node_engine = node_vld->get_node_engine();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();

  this->vk_screenshot = node_vulkan->get_vk_screenshot();

  //---------------------------
}
Screenshot::~Screenshot(){}

//Main function
void Screenshot::start_thread(){
  //---------------------------

  if(!thread_running){
    //this->thread = std::thread(&Screenshot::run_thread, this);
  }

  //---------------------------
  this->thread_idle = false;
}
void Screenshot::run_thread(){
  this->thread_running = true;
  //---------------------------

  //Playback thread
  while(thread_running){
    vk_screenshot->make_screenshot();
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
  }

  //---------------------------
  this->thread_idle = true;
}
void Screenshot::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

}
