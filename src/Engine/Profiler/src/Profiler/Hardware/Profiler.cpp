#include "Profiler.h"

#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  this->prf_struct = new prf::hardware::Structure();
  this->prf_collector = new prf::hardware::Collector(prf_struct);

  this->name = "Hardware";
  this->type = prf::base::HARDWARE;

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::collect_info(vk::structure::Vulkan* vk_struct){
  //---------------------------

  prf_collector->collect_info(vk_struct);

  //---------------------------
}
void Profiler::add_queue(prf::hardware::queue::Type type, int ID_family){
  //---------------------------

  prf::hardware::Queue queue;
  queue.type = type;
  queue.number++;
  queue.family_ID = ID_family;
  queue.thread_ID = utl::thread::get_ID_str();
  prf_struct->vec_queue.push_back(queue);

  //---------------------------
}

}
