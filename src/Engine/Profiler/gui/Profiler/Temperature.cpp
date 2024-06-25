#include "Temperature.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::gui{

//Constructor / Destructor
Temperature::Temperature(prf::Node* node_profiler){
  //---------------------------

  this->gui_plot = new utl::implot::Plot();
  this->prf_temp = new prf::temp::Profiler();

  //---------------------------
}
Temperature::~Temperature(){}

//Main function
void Temperature::draw_profiler(prf::temp::Profiler* temperature){
  //---------------------------



  float cpu_temp = prf_temp->find_CPU_temperature();
  float gpu_temp = prf_temp->find_GPU_temperature();

  gui_plot->plot_temperature(cpu_temp, gpu_temp);

  //---------------------------
}

//Tab function


}
