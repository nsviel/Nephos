#include "Profiler.h"

#include <Profiler/Namespace.h>


namespace prf::vulkan{

//Constructor / Destructor
Profiler::Profiler(string name, string type) : prf::type::Profiler(name, type){
  //---------------------------

  this->info_vulkan = new prf::vulkan::Info();

  //---------------------------
}
Profiler::~Profiler(){}

//Main function


}
