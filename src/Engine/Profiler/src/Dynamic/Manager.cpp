#include "Manager.h"

#include <Profiler/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::dynamic{

//Constructor / Destructor
Manager::Manager(prf::Node* node_profiler){
  //---------------------------

  vk::Node* node_vulkan = node_profiler->get_node_vulkan();

  this->prf_struct = node_profiler->get_prf_struct();
  this->vk_struct = node_vulkan->get_vk_struct();

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  this->add_profiler(&prf_struct->dynamic.profiler_main, "Main");

  //---------------------------
}
void Manager::loop(int max_fps){
  //---------------------------

  //CPU tasker
  prf::dynamic::Tasker* tasker_cpu = prf_struct->dynamic.profiler_main.fetch_tasker("cpu");
  tasker_cpu->loop(max_fps);

  //GPU tasker
  prf::dynamic::Tasker* tasker_gpu = prf_struct->dynamic.profiler_main.fetch_tasker("gpu");
  tasker_gpu->loop();
  this->collect_gpu_task();

  //---------------------------
}

//Subfunction
void Manager::add_profiler(prf::dynamic::Profiler* profiler, std::string name){
  //---------------------------

  profiler->name = name;
  prf_struct->dynamic.list_profiler.push_back(profiler);

  //---------------------------
}
void Manager::remove_profiler(prf::dynamic::Profiler* profiler){
  //---------------------------

  profiler->clean();
  prf_struct->dynamic.list_profiler.remove(profiler);
  //delete profiler;

  //---------------------------
}
void Manager::collect_gpu_task(){
  prf::dynamic::Tasker* tasker = prf_struct->dynamic.profiler_main.fetch_tasker("gpu");
  //---------------------------

  float ts_current = 0;
  for(int i=0; i<vk_struct->profiler.vec_command_buffer.size(); i++){
    std::string& name = vk_struct->profiler.vec_command_buffer[i].name;
    float& duration = vk_struct->profiler.vec_command_buffer[i].duration;

    tasker->add_task(name, ts_current, ts_current + duration);
    ts_current += duration;
  }

  //---------------------------
}
prf::dynamic::Tasker* Manager::get_tasker_cpu(){
  //---------------------------

  return prf_struct->dynamic.profiler_main.fetch_tasker("cpu");

  //---------------------------
}

}
