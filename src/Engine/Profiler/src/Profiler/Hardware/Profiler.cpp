#include "Profiler.h"

#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  //this->rnd_cpu = new utl::hardare::CPU();
  //this->rnd_gpu = new utl::hardare::Nvidia();
  this->name = "Hardware";

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::update_tic(){
  //---------------------------
/*
  static int cpt = 0;
  static float max_gpu = 0;
  static float max_cpu = 0;

  int temp_cpu = rnd_cpu->get_temperature();
  int temp_gpu = rnd_gpu->get_temperature();
  cpt++;

  cpu_temps.push_back(temp_cpu);
  gpu_temps.push_back(temp_gpu);
  vec_time.push_back(cpt);

  if(cpu_temps.size() > nb_element) cpu_temps.erase(cpu_temps.begin());
  if(gpu_temps.size() > nb_element) gpu_temps.erase(gpu_temps.begin());
  if(vec_time.size() > nb_element) vec_time.erase(vec_time.begin());

  float max_current_cpu = (float)*std::max_element(cpu_temps.begin(), cpu_temps.end());
  float max_current_gpu = (float)*std::max_element(gpu_temps.begin(), gpu_temps.end());
  if(max_current_cpu > max_cpu) max_cpu = max_current_cpu;
  if(max_current_gpu > max_gpu) max_gpu = max_current_gpu;
*/
  //---------------------------
}

//Subfunction


}
