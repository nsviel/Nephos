#include "Profiler.h"

#include <Profiler/Namespace.h>


namespace prf{

//Constructor / Destructor
Profiler::Profiler(string name, string type){
  //---------------------------

  this->name = name;
  this->type = type;
  this->fps_control = new prf::fps::Control(120);
  this->fps_counter = new prf::fps::Counter();
  this->gui_graph = new prf::improfil::Manager(name);
  this->is_fps_control = false;

  //---------------------------
}
Profiler::~Profiler(){
  //---------------------------

  delete fps_control;
  delete fps_counter;
  delete gui_graph;

  //---------------------------
}

//Main function


}
