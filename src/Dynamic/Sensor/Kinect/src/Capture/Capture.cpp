#include "Capture.h"

#include <Kinect/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Capture::Capture(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::init_device(k4n::capture::Sensor& sensor){
  //---------------------------

  //Open device
  sensor.device.handle = k4a::device::open(sensor.device.index);
  if(!sensor.device.handle.is_valid()) return;

  //Get device info
  sensor.name = "capture_" + std::to_string(sensor.device.index);
  sensor.data.name = sensor.name;
  sensor.info.serial_number = sensor.device.handle.get_serialnum();
  sensor.info.vec_recorder.push_back(new k4n::capture::Recorder());
  sensor.device.version = sensor.device.handle.get_version();
  sensor.device.capture = std::make_shared<k4a::capture>();
  
  //---------------------------
}
void Capture::init_capture(k4n::capture::Sensor& sensor){
  //---------------------------

  sensor.device.handle.start_cameras(&sensor.device.configuration);

  //---------------------------
}

}
