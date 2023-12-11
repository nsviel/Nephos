#include "Capture.h"


namespace util::capture{

//Constructor / Destructor
Capture::Capture(){
  //---------------------------

  this->kinect = new Kinect();

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::init(){
  //---------------------------

  kinect->init();

  //---------------------------
}
void Capture::run(){
  //---------------------------

  //---------------------------
}
void Capture::clean(){
  //---------------------------



  //---------------------------
}

}
