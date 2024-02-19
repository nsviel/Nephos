#include "Processing.h"

#include <Utility/Namespace.h>
#include <K4N/Namespace.h>
#include <chrono>


namespace k4n::thread{

//Constructor / Destructor
Processing::Processing(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_swarm = node_k4n->get_k4n_swarm();

  //---------------------------
}
Processing::~Processing(){}

//Main function
void Processing::start_thread(){
  //---------------------------

  this->thread = std::thread(&Processing::run_thread, this);

  //---------------------------
}
void Processing::run_thread(){
  //---------------------------



  //---------------------------
}

//Subfunction


}
