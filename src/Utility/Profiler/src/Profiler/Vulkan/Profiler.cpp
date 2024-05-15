#include "Profiler.h"

#include <Profiler/Namespace.h>


namespace prf::vulkan{

//Constructor / Destructor
Profiler::Profiler(string name, string type) : prf::type::Profiler(name, type){
  //---------------------------

  this->info = new prf::vulkan::Info();

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
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
void Profiler::add_queue(prf::vulkan::Queue_type type, int ID_family){
  //---------------------------

  prf::vulkan::Queue& queue = map_queue[type];
  queue.number++;
  queue.ID_family = ID_family;

  //---------------------------
}

}
