#include "Configuration.h"

#include <Kinect/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Configuration::Configuration(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Configuration::~Configuration(){}

//Main function


}
