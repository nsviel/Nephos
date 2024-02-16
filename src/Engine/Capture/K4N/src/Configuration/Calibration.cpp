#include "Calibration.h"


namespace k4n::config{

//Constructor / Destructor
Calibration::Calibration(){
  //---------------------------


  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::make_device_transformation(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  k4n_sensor->param.transformation = k4a::transformation(k4n_sensor->param.calibration);

  //---------------------------
}
void Calibration::make_capture_calibration(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  k4n_sensor->param.calibration = k4n_sensor->param.device->get_calibration(k4n_sensor->depth.config.mode, k4n_sensor->color.config.resolution);

  //---------------------------
}
void Calibration::find_playback_calibration(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  k4n_sensor->param.calibration = k4n_sensor->param.playback->get_calibration();

  //---------------------------
}

}
