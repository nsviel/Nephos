#include "Registration.h"

#include <Kinect/Namespace.h>
#include <Radiometry/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Registration::Registration(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();

  //---------------------------
}
Registration::~Registration(){}

//Main function
void Registration::draw_registration(k4n::dev::Device* sensor){
  //---------------------------



  //---------------------------
}

//Subfunction

}
