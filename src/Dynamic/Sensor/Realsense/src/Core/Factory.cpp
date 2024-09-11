#include "Factory.h"

#include <Realsense/Namespace.h>
#include <Data/Namespace.h>


namespace rlx{

//Constructor / Destructor
Factory::Factory(rlx::Node* node_realsense){
  //---------------------------

  dat::Node* node_data = node_realsense->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->node_realsense = node_realsense;
  this->dat_set = node_element->get_dat_set();
  this->dat_graph = node_graph->get_gph_graph();

  //---------------------------
}
Factory::~Factory(){}

//Main function
std::shared_ptr<rlx::capture::Sensor> Factory::create_capture_sensor(){
  //---------------------------

  //Create sensor
  std::shared_ptr<rlx::capture::Sensor> sensor = std::make_shared<rlx::capture::Sensor>(node_realsense);

  //Insert sensor into data tree
  this->insert_in_set(*sensor);

  //---------------------------
  return sensor;
}
std::shared_ptr<rlx::playback::Sensor> Factory::create_playback_sensor(utl::base::Path path){
  //---------------------------

  //Create sensor
  std::shared_ptr<rlx::playback::Sensor> sensor = std::make_shared<rlx::playback::Sensor>(node_realsense);

  //Insert sensor into data tree
  this->insert_in_set(*sensor);

  //---------------------------
  return sensor;
}

//Subfunction
void Factory::insert_in_set(rlx::base::Sensor& sensor){
  //---------------------------

  //Get kinect set
  std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
  std::shared_ptr<dat::base::Set> set = dat_set->get_subset(set_graph, "realsense");

  //If it doesn't exists, create it
  if(!set){
    set = std::make_shared<dat::base::Set>();
    set->name = "realsense";
    set->icon = ICON_FA_USER;
    set->is_locked = false;
    set->is_suppressible = true;
    dat_set->add_subset(set_graph, set);
  }

  //Assign to sensor
  sensor.set_parent = set;

  //---------------------------
}

}
