#include "Profiler.h"

#include <Profiler/Namespace.h>
#include <Render/Namespace.h>
#include <nvml.h>


namespace prf::temp{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  this->rnd_cpu = new rnd::hardare::CPU();
  this->rnd_gpu = new rnd::hardare::Nvidia();
  this->name = "Hardware";

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::reset(){
  //---------------------------



  //---------------------------
}

//Subfunction


}
