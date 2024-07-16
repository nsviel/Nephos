#include "Operation.h"

#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::cloud{

//Constructor / Destructor
Operation::Operation(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();
  ope::Node* node_operation = node_dynamic->get_node_operation();

  this->dat_entity = node_data->get_dat_entity();
  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_normal = new dyn::cloud::Normal(node_dynamic);
  this->dyn_recorder = new dyn::cloud::Recorder(node_dynamic);
  this->dyn_radio = new dyn::cloud::Radiometry(node_dynamic);
  this->ope_colorizer = new ope::color::Routine(node_operation);

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
  //ope_colorizer->start_task(sensor);
  ope_colorizer->colorize_entity(sensor);
  dat_entity->update_data(sensor);

  //---------------------------
}
void Operation::wait_operation(){
  //---------------------------

  dyn_recorder->wait_thread();
  //dyn_normal->wait_thread();
  //dyn_radio->wait_thread();


  //---------------------------
}

}
