#include "Calibration.h"


namespace k4n::config{

//Constructor / Destructor
Calibration::Calibration(){
  //---------------------------


  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::make_device_transformation(k4n::dev::Sensor* sensor){
  //---------------------------

  sensor->param.transformation = k4a::transformation(sensor->param.calibration);

  //---------------------------
}
void Calibration::make_capture_calibration(k4n::dev::Sensor* sensor){
  //---------------------------

  k4a::device& device = sensor->param.device;
  sensor->param.calibration = device.get_calibration(sensor->depth.config.mode, sensor->color.config.resolution);

  //---------------------------
}
void Calibration::find_playback_calibration(k4n::dev::Sensor* sensor){
  //---------------------------

  sensor->param.calibration = sensor->param.playback.get_calibration();

  //---------------------------
}

}
