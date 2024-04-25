#include "Calibration.h"


namespace k4n::config{

//Constructor / Destructor
Calibration::Calibration(){
  //---------------------------


  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::make_transformation_from_calibration(k4n::dev::Sensor* sensor){
  //---------------------------

  sensor->param.transformation = k4a::transformation(sensor->param.calibration);

  //---------------------------
}
void Calibration::make_capture_calibration(k4n::dev::Sensor* sensor){
  k4n::dev::Master* master = sensor->master;
  k4a::device& device = sensor->param.device;
  //---------------------------

  sensor->param.calibration = device.get_calibration(master->config.depth.mode, master->config.color.resolution);

  //---------------------------
}
void Calibration::find_playback_calibration(k4n::dev::Sensor* sensor){
  //---------------------------

  sensor->param.calibration = sensor->param.playback.get_calibration();

  //---------------------------
}

}
