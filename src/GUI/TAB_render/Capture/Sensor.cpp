#include "Sensor.h"

#include <GUI.h>


namespace gui::kinect{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_kinect){
  //---------------------------

  this->node_kinect = node_kinect;
  this->k4n_swarm = node_kinect->get_k4n_swarm();

  this->item_width = 100;

  //---------------------------
}
Sensor::~Sensor(){}

//Main function


}
