#include "Hardware.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::gui{

//Constructor / Destructor
Hardware::Hardware(prf::Node* node_profiler){
  //---------------------------

  this->gui_plot = new utl::implot::Plot();
  this->prf_temp = new prf::hardware::Profiler();

  //---------------------------
}
Hardware::~Hardware(){}

//Main function
void Hardware::show_profiler(prf::base::Profiler* profiler){
  //---------------------------



  //float cpu_temp = prf_temp->find_CPU_temperature();
  //float gpu_temp = prf_temp->find_GPU_temperature();

  //gui_plot->plot_temperature(cpu_temp, gpu_temp);

  //---------------------------
}

//Tab function


}
