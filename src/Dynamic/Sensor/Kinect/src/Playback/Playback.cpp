#include "Playback.h"

#include <Kinect/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Playback::Playback(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::init_playback(k4n::playback::Sensor& sensor){
  //---------------------------

  //Set sensor info
  sensor.name = sensor.data.path.name;
  sensor.data.name = sensor.data.path.name;
  sensor.data.path.format = sensor.data.path.format;

  //Init playback object
  std::string path = sensor.data.path.build();
  if(path == "") return;
  sensor.playback = k4a::playback::open(path.c_str());

  //Check validity
  if(!sensor.playback){
    std::cout<<"[error] Kinect sensor playback init"<<std::endl;
  }

  //---------------------------
}
void Playback::close_playback(k4n::playback::Sensor& sensor){
  //---------------------------

  sensor.playback.close();

  //---------------------------
}

}
