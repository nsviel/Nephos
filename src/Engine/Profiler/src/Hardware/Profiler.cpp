#include "Profiler.h"

#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
Profiler::Profiler(prf::Node* node_profiler){
  //---------------------------

  this->prf_struct = node_profiler->get_prf_struct();
  this->prf_collector = new prf::hardware::Collector(node_profiler);

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::init(){
  //---------------------------

  prf_collector->collect_info();

  //---------------------------
}
void Profiler::add_queue(prf::hardware::queue::Type type, int ID_family){
  //---------------------------

  prf::hardware::Queue queue;
  queue.type = type;
  queue.number++;
  queue.family_ID = ID_family;
  queue.thread_ID = utl::thread::get_ID_str();
  prf_struct->hardware.gpu.vec_queue.push_back(queue);

  //---------------------------
}

}
