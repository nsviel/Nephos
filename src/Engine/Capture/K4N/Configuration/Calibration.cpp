#include "Calibration.h"


namespace k4n::config{

//Constructor / Destructor
Calibration::Calibration(){
  //---------------------------


  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::make_device_transformation(k4n::Sensor* k4n_sensor){
  //---------------------------

  k4n_sensor->device.transformation = k4a::transformation(k4n_sensor->device.calibration);

  //---------------------------
}
void Calibration::make_capture_calibration(k4n::Sensor* k4n_sensor){
  //---------------------------

  k4n_sensor->device.calibration = k4n_sensor->device.device->get_calibration(k4n_sensor->depth.config.mode, k4n_sensor->color.config.resolution);

  //---------------------------
}
void Calibration::find_playback_calibration(k4n::Sensor* k4n_sensor){
  //---------------------------

  k4n_sensor->device.calibration = k4n_sensor->device.playback->get_calibration();

  //---------------------------
}

}
