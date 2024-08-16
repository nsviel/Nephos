#include "Operation.h"

#include <Utility/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::prc::cloud{

//Constructor / Destructor
Operation::Operation(dyn::prc::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();
  dat::atr::Node* node_attribut = node_data->get_node_attribut();

  this->dat_entity = node_element->get_dat_entity();
  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_normal = new dyn::prc::cloud::Normal(node_dynamic);
  this->dyn_recorder = new dyn::prc::cloud::Recorder(node_dynamic);
  this->dyn_radio = new dyn::prc::cloud::Radiometry(node_dynamic);
  this->atr_color = new dat::atr::Color(node_attribut);

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::run_operation(dyn::prc::base::Sensor* sensor){
  //---------------------------

  dyn_recorder->start_thread(sensor);
  //dyn_normal->start_thread(sensor);
  //dyn_radio->start_thread(sensor);

  //The troutine pose probleme, is faut qu'il soit dédié à un sensor
  //pour l'instant c'est la meme qqsoit le sensor
  //Du coup 2 playback = laggs
  //atr_color->start_task(sensor);
  atr_color->make_colorization(sensor);


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
