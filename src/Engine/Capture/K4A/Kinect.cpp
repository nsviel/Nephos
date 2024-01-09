#include "Kinect.h"

#include <Engine/Engine.h>


namespace eng::kinect{

//Constructor / Destructor
Kinect::Kinect(Engine* engine){
  //---------------------------

  this->k4a_swarm = new K4A_swarm(engine);

  //---------------------------
}
Kinect::~Kinect(){}

//Main function
void Kinect::init(){
  //---------------------------

  k4a_swarm->manage_no_device();

  //---------------------------
}
void Kinect::loop(){
  //---------------------------

  k4a_swarm->refresh_connected_device();
  k4a_swarm->draw_all_clouds();

  //---------------------------
}
void Kinect::reset(){
  //---------------------------

  k4a_swarm->reset_all_device();

  //---------------------------
}


}
