#include "Profiler.h"

#include <Profiler/Namespace.h>


namespace prf::vulkan{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  this->prf_struct = new prf::vulkan::Info();
  this->prf_collector = new prf::vulkan::Collector(prf_struct);

  //---------------------------
}
Profiler::Profiler(string name, string type){
  //---------------------------

  this->prf_struct = new prf::vulkan::Info();
  this->prf_collector = new prf::vulkan::Collector(prf_struct);
  this->name = name;
  this->type = type;

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::collect_info(vk::structure::Vulkan* vk_struct){
  //---------------------------

  prf_collector->collect_info(vk_struct);

  //---------------------------
}
void Profiler::add_thread(string name){
  mutex.lock();
  //---------------------------

  prf::vulkan::Thread thread;
  thread.ID = std::this_thread::get_id();
  thread.name = name;

  vec_thread.push_back(thread);

  //---------------------------
  mutex.unlock();
}
void Profiler::add_queue(prf::vulkan::queue::Type type, int ID_family){
  //---------------------------

  prf::vulkan::Queue& queue = map_queue[type];
  queue.number++;
  queue.ID_family = ID_family;

  //---------------------------
}

}
