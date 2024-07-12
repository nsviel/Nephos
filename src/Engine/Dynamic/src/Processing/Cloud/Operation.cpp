#include "Operation.h"

#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>


namespace dyn::cloud{

//Constructor / Destructor
Operation::Operation(dyn::Node* node_dynamic){
  //---------------------------

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_normal = new dyn::cloud::Normal(node_dynamic);
  this->dyn_recorder = new dyn::cloud::Recorder(node_dynamic);
  this->dyn_radio = new dyn::cloud::Radiometry(node_dynamic);
  this->dyn_colorizer = new dyn::cloud::Colorizer(node_dynamic);

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::run_operation(dyn::base::Sensor* sensor){
  //---------------------------

  dyn_recorder->start_thread(sensor);
  //dyn_normal->start_thread(sensor);
  //dyn_radio->start_thread(sensor);

  //The troutine pose probleme, is faut qu'il soit dédié à un sensor
  //pour l'instant c'est la meme qqsoit le sensor
  //Du coup 2 playback = laggs
  //dyn_colorizer->start_task(sensor);
  dyn_colorizer->colorize_object(sensor);
  dyn_colorizer->update_object(sensor);

  //---------------------------
}
void Operation::wait_operation(){
  //---------------------------

  dyn_recorder->wait_thread();
  //dyn_normal->wait_thread();
  //dyn_radio->wait_thread();
  dyn_colorizer->wait_task();

  //---------------------------
}

}
