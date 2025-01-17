#include "CPU.h"

#include <Hardware/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
CPU::CPU(prf::hardware::Node* node_hardware){
  //---------------------------

  this->prf_struct = node_hardware->get_prf_struct();
  this->utl_cpu = new sys::hardware::CPU();

  //---------------------------
}
CPU::~CPU(){}

//Main function
void CPU::collect_cpu_info(){
  //---------------------------

  prf_struct->cpu.name = utl_cpu->get_name();
  prf_struct->cpu.nb_core = utl_cpu->get_number_of_core();
  prf_struct->cpu.temperature_max = utl_cpu->get_temperature_max();

  //---------------------------
}
void CPU::collect_cpu_variable(){
  //---------------------------

  prf_struct->cpu.temperature = utl_cpu->get_temperature();

  //---------------------------
}

}
