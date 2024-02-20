#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf::vulkan{

//Constructor / Destructor
Manager::Manager(string name) : Tasker(name){
  //---------------------------

  this->info_vulkan = new prf::vulkan::Info();

  //---------------------------
}
Manager::~Manager(){}

//Main function


}
