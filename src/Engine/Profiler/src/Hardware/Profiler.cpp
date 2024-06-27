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
void Profiler::loop(){
  //---------------------------

  prf_collector->collect_gpu_info();

  //---------------------------
}

}
