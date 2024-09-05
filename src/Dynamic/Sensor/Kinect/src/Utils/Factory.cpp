#include "Factory.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n{

//Constructor / Destructor
Factory::Factory(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->node_k4n = node_k4n;
  this->dat_set = node_element->get_dat_set();
  this->dat_graph = node_graph->get_gph_graph();

  //---------------------------
}
Factory::~Factory(){}

//Main function
std::shared_ptr<k4n::capture::Sensor> Factory::create_capture_sensor(int index){
  //---------------------------

  //Create sensor
  std::shared_ptr<k4n::capture::Sensor> sensor = std::make_shared<k4n::capture::Sensor>(node_k4n, index);

  //Insert sensor into data tree
  this->insert_in_kinect_set(*sensor);

  //---------------------------
  return sensor;
}
std::shared_ptr<k4n::playback::Sensor> Factory::create_playback_sensor(utl::base::Path path){
  //---------------------------

  //Create sensor
  std::shared_ptr<k4n::playback::Sensor> sensor = std::make_shared<k4n::playback::Sensor>(node_k4n, path);

  //Insert sensor into data tree
  this->insert_in_kinect_set(*sensor);

  //---------------------------
  return sensor;
}

//Subfunction
void Factory::insert_in_kinect_set(k4n::base::Sensor& sensor){
  //---------------------------

  //Get kinect set
  std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
  std::shared_ptr<dat::base::Set> set = dat_set->get_subset(set_graph, "kinect");

  //If it doesn't exists, create it
  if(!set){
    set = std::make_shared<dat::base::Set>();
    set->name = "kinect";
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
