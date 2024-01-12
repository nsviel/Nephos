#include "Calibration.h"


namespace k4n::config{

//Constructor / Destructor
Calibration::Calibration(){
  //---------------------------


  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::make_device_transformation(k4n::Device* k4n_device){
  //---------------------------

  k4n_device->device.transformation = k4a::transformation(k4n_device->device.calibration);

  //---------------------------
}
void Calibration::make_capture_calibration(k4n::Device* k4n_device){
  //---------------------------

  k4n_device->device.calibration = k4n_device->device.device->get_calibration(k4n_device->depth.config.mode, k4n_device->color.config.resolution);

  //---------------------------
}
void Calibration::find_playback_calibration(k4n::Device* k4n_device){
  //---------------------------

  k4n_device->device.calibration = k4n_device->device.playback->get_calibration();

  //---------------------------
}

}
