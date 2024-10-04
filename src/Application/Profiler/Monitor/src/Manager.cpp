#include "Manager.h"

#include <Monitor/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::monitor{

//Constructor / Destructor
Manager::Manager(prf::monitor::Node* node_monitor){
  //---------------------------

  vk::Node* node_vulkan = node_monitor->get_node_vulkan();

  this->prf_struct = node_monitor->get_prf_struct();
  this->vk_struct = node_vulkan->get_vk_struct();

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  this->add_profiler(&prf_struct->profiler_main, "Main");

  //---------------------------
}
void Manager::loop(int max_fps){
  prf::monitor::Profiler* profiler = &prf_struct->profiler_main;
  //---------------------------

  //CPU tasker
  prf::monitor::Tasker* tasker_cpu = profiler->fetch_tasker("cpu");
  tasker_cpu->loop(max_fps);

  //GPU tasker
  prf::monitor::Tasker* tasker_gpu = profiler->fetch_tasker("gpu");
  tasker_gpu->loop();
  this->collect_gpu_task();


  std::list<prf::monitor::Tasker*> list_tasker = profiler->get_list_tasker();
  //say(list_tasker.size());

  //---------------------------
}

//Subfunction
void Manager::add_profiler(prf::monitor::Profiler* profiler, std::string name){
  //---------------------------

  profiler->name = name;
  prf_struct->list_profiler.push_back(profiler);

  //---------------------------
}
void Manager::remove_profiler(prf::monitor::Profiler* profiler){
  //---------------------------

  profiler->clean();
  prf_struct->list_profiler.remove(profiler);
  //delete profiler;

  //---------------------------
}
void Manager::collect_gpu_task(){
  prf::monitor::Tasker* tasker = prf_struct->profiler_main.fetch_tasker("gpu");
  //---------------------------

  float ts_current = 0;
  for(auto& [name, duration] : vk_struct->core.profiler.map_duration){
    tasker->add_task(name, ts_current, ts_current + duration);
    ts_current += duration;
  }

  //---------------------------
}
prf::monitor::Tasker* Manager::get_tasker_cpu(){
  prf::monitor::Profiler* profiler = &prf_struct->profiler_main;
  //---------------------------

  prf::monitor::Tasker* tasker_cpu = profiler->fetch_tasker("cpu");

  //---------------------------
  return tasker_cpu;
}

}
