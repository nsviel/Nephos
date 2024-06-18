#include "Radiometry.h"

#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Utility/Namespace.h>


namespace dyn::cloud{

//Constructor / Destructor
Radiometry::Radiometry(dyn::Node* node_dynamic){
  //---------------------------

  rad::Node* node_radio = node_dynamic->get_node_radio();

  //---------------------------
}
Radiometry::~Radiometry(){}

//Main function
void Radiometry::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  if(thread.joinable()){
    this->thread.join();
  }
  this->thread = std::thread(&Radiometry::run_thread, this, sensor);

  //---------------------------
}
void Radiometry::run_thread(dyn::base::Sensor* sensor){
  //---------------------------

  //---------------------------
  this->thread_idle = true;
}
void Radiometry::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

}
