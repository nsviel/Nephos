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
void Kinect::loop(){
  //---------------------------

  k4a_swarm->refresh_connected_device();
  k4a_swarm->draw_all_clouds();

  //---------------------------
}

}
