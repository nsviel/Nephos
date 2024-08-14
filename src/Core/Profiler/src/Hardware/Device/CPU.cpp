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

//Main function
void CPU::collect_cpu_info(){
  //---------------------------

  prf_struct->hardware.cpu.name = utl_cpu->get_name();
  prf_struct->hardware.cpu.nb_core = utl_cpu->get_number_of_core();
  prf_struct->hardware.cpu.temperature_max = utl_cpu->get_temperature_max();

  //---------------------------
}
void CPU::collect_cpu_variable(){
  //---------------------------

  prf_struct->hardware.cpu.temperature = utl_cpu->get_temperature();

  //---------------------------
}

}
