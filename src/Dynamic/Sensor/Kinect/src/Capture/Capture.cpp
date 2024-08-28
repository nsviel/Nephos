#include "Capture.h"

#include <Kinect/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Capture::Capture(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Capture::~Capture(){}

//Main function


}
