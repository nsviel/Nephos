#include "Capture.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Capture::Capture(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();
  dat::img::Node* node_image = node_data->get_node_image();

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_config = new k4n::capture::Configuration(node_k4n);
  this->dat_sensor = node_element->get_dat_sensor();
  this->dat_image = node_image->get_dat_image();

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::init(k4n::capture::Sensor& sensor){
  //---------------------------

  this->init_info(sensor);
  this->init_device(sensor);
  dat_sensor->init_sensor(sensor);
  k4n_config->init_configuration(sensor);
  this->init_capture(sensor);

  //---------------------------
}
void Capture::capture(dat::base::Sensor& sensor){
  k4n::capture::Sensor* k4n_sensor = dynamic_cast<k4n::capture::Sensor*>(&sensor);
  //---------------------------

  prf::monitor::Tasker* tasker = sensor.profiler.fetch_tasker("capture");
  tasker->loop();
  tasker->task_begin("data");

  //Capture data
  bool ok = k4n_sensor->device.handle.get_capture(k4n_sensor->device.capture.get(), std::chrono::milliseconds(2000));

  //Check capture
  if(!ok){
    k4n_sensor->device.capture.reset();
  }

  tasker->task_end("data");

  //---------------------------
}
void Capture::clean(k4n::capture::Sensor& sensor){
  //---------------------------

  dat_sensor->clean_sensor(sensor);
  this->close_capture(sensor);
  k4n_struct->connection.current_ID--;

  //---------------------------
}

//Subfunction
void Capture::init_info(k4n::capture::Sensor& sensor){
  //---------------------------

  sensor.type_sensor = "capture";
  sensor.device.index = k4n_struct->connection.current_ID++;
  sensor.name = "capture_" + std::to_string(sensor.device.index);
  sensor.calibration.path.insert("../media/calibration/kinect.json");

  sensor.info.vec_recorder.push_back(new k4n::capture::Recorder());
  sensor.info.model = "kinect";
  sensor.info.depth_mode = "NFOV";
  sensor.info.vec_depth_mode.push_back("NFOV");
  sensor.info.vec_depth_mode.push_back("WFOV");

  sensor.data->name = sensor.name;
  sensor.data->topology.type = utl::topology::POINT;
  sensor.data->size_max = 10000000;
  sensor.data->path.format = ".mkv";
  sensor.data->path.directory = utl::path::get_current_path_abs();
  sensor.pose->model[2][3] = 1;

  //---------------------------
}
void Capture::init_device(k4n::capture::Sensor& sensor){
  //---------------------------

  //Wait until driver ready
  int nb_device =0;
  while(nb_device ==0){
    nb_device = k4a_device_get_installed_count();
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

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
void Capture::close_capture(k4n::capture::Sensor& sensor){
  //---------------------------

  sensor.device.handle.stop_cameras();
  sensor.device.handle.close();

  //---------------------------
}

}
