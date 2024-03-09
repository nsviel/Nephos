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
  //---------------------------

  prf::vulkan::Thread thread;
  thread.ID = std::this_thread::get_id();
  thread.name = name;

  vec_thread.push_back(thread);

  //---------------------------
}
void Profiler::add_queue(int type, int ID_family){
  //---------------------------

  prf::vulkan::Queue queue;
  queue.type = type;
  queue.ID_family = ID_family;

  vec_queue.push_back(queue);

  //---------------------------
}

}
