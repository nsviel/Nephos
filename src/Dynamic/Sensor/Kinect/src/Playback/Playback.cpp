#include "Playback.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Playback::Playback(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_config = new k4n::playback::Configuration(node_k4n);
  this->dat_sensor = node_element->get_dat_sensor();

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::init(k4n::playback::Sensor& sensor){
  //---------------------------

  this->init_info(sensor);
  this->init_playback(sensor);
  this->init_timestamp(sensor);
  dat_sensor->init_sensor(sensor);
  k4n_config->init_configuration(sensor);

  //---------------------------
}
void Playback::clean(k4n::playback::Sensor& sensor){
  //---------------------------

  dat_sensor->clean_sensor(sensor);
  this->close_playback(sensor);

  //---------------------------
}

//Subfunction
void Playback::init_info(k4n::playback::Sensor& sensor){
  //---------------------------

  sensor.name = sensor.data->path.name;
  sensor.calibration.path.insert("../media/calibration/kinect.json");

  sensor.data->name = sensor.data->path.name;
  sensor.data->topology.type = utl::topology::POINT;
  sensor.data->nb_data_max = 10000000;

  sensor.info.model = "kinect";
  sensor.info.depth_mode = "NFOV";
  sensor.info.vec_depth_mode.push_back("NFOV");
  sensor.info.vec_depth_mode.push_back("WFOV");

  //---------------------------
}
void Playback::init_playback(k4n::playback::Sensor& sensor){
  //---------------------------

  //Init playback object
  std::string path = sensor.data->path.build();
  if(path == "") return;
  sensor.device.playback = k4a::playback::open(path.c_str());

  //Check validity
  if(!sensor.device.playback){
    std::cout<<"[error] Kinect sensor playback init"<<std::endl;
  }

  //---------------------------
}
void Playback::init_timestamp(k4n::playback::Sensor& sensor){
  //---------------------------

  sensor.timestamp.begin = k4n_config->find_mkv_ts_beg(sensor.data->path.build());
  sensor.timestamp.end = k4n_config->find_mkv_ts_end(sensor.data->path.build());
  sensor.timestamp.duration = sensor.timestamp.end - sensor.timestamp.begin;

  //---------------------------
}
void Playback::close_playback(k4n::playback::Sensor& sensor){
  //---------------------------

  sensor.device.playback.close();

  //---------------------------
}
void Playback::manage_capture(dat::base::Sensor& sensor){
  k4n::playback::Sensor* k4n_sensor = dynamic_cast<k4n::playback::Sensor*>(&sensor);
  //---------------------------

  prf::monitor::Tasker* tasker = sensor.profiler.fetch_tasker("capture");
  tasker->loop();
  tasker->task_begin("data");

  //Capture data
  bool ok = k4n_sensor->device.playback.get_next_capture(k4n_sensor->device.capture.get());

  //Check capture
  if(!ok){
    k4n_sensor->device.capture.reset();
  }

  tasker->task_end("data");

  //---------------------------
}

}
