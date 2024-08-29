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
void Capture::init_info(k4n::capture::Sensor& sensor){
  //---------------------------

  sensor.name = "capture_" + std::to_string(sensor.device.index);
  sensor.calibration.path.insert("../media/calibration/kinect.json");
  sensor.device.capture = std::make_shared<k4a::capture>();

  sensor.info.vec_recorder.push_back(new k4n::capture::Recorder());
  sensor.info.model = "kinect";
  sensor.info.depth_mode = "NFOV";
  sensor.info.vec_depth_mode.push_back("NFOV");
  sensor.info.vec_depth_mode.push_back("WFOV");

  sensor.data.name = sensor.name;
  sensor.data.topology.type = utl::topology::POINT;
  sensor.data.nb_data_max = 10000000;

  //---------------------------
}
void Capture::init_device(k4n::capture::Sensor& sensor){
  //---------------------------

  //Open device
  sensor.device.handle = k4a::device::open(sensor.device.index);
  if(!sensor.device.handle.is_valid()) return;

  //Get device info
  sensor.info.serial_number = sensor.device.handle.get_serialnum();
  sensor.device.version = sensor.device.handle.get_version();

  //---------------------------
}
void Capture::init_capture(k4n::capture::Sensor& sensor){
  //---------------------------

  sensor.device.handle.start_cameras(&sensor.device.configuration);

  //---------------------------
}

}
