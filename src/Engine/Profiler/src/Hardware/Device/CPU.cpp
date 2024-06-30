#include "CPU.h"

#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
CPU::CPU(prf::Node* node_profiler){
  //---------------------------

  this->prf_struct = node_profiler->get_prf_struct();
  this->utl_cpu = new utl::hardware::CPU();

  //---------------------------
}
CPU::~CPU(){}

//Profiler vulkan info
void CPU::collect_info(){
  //---------------------------

  this->collect_cpu_info();

  //---------------------------
}

//Subfunction
void CPU::collect_cpu_info(){
  //---------------------------

  prf_struct->hardware.cpu.name = utl_cpu->get_name();
  prf_struct->hardware.cpu.temperature = utl_cpu->get_temperature();
  prf_struct->hardware.cpu.nb_core = utl_cpu->get_number_of_core();

  //---------------------------
}


}
