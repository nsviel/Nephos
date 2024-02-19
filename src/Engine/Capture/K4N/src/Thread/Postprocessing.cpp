#include "Postprocessing.h"

#include <Utility/Namespace.h>
#include <K4N/Namespace.h>
#include <chrono>


namespace k4n::thread{

//Constructor / Destructor
Postprocessing::Postprocessing(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_swarm = node_k4n->get_k4n_swarm();

  //---------------------------
}
Postprocessing::~Postprocessing(){}

//Main function
void Postprocessing::start_thread(){
  //---------------------------

  this->thread = std::thread(&Postprocessing::run_thread, this);

  //---------------------------
}
void Postprocessing::run_thread(){
  //---------------------------



  //---------------------------
}

//Subfunction


}
