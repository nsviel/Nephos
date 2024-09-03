#include "Playback.h"

#include <Kinect/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Playback::Playback(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::init_info(k4n::playback::Sensor& sensor){
  //---------------------------

  sensor.name = sensor.data.path.name;
  sensor.device.capture = std::make_shared<k4a::capture>();
  sensor.color.image = std::make_shared<utl::media::Image>();
  sensor.depth.image = std::make_shared<utl::media::Image>();
  sensor.infra.image = std::make_shared<utl::media::Image>();
  sensor.calibration.path.insert("../media/calibration/kinect.json");

  sensor.data.name = sensor.data.path.name;
  sensor.data.topology.type = utl::topology::POINT;
  sensor.data.nb_data_max = 10000000;

  sensor.info.model = "kinect";
  sensor.info.depth_mode = "NFOV";
  sensor.info.vec_depth_mode.push_back("NFOV");
  sensor.info.vec_depth_mode.push_back("WFOV");

  //---------------------------
}
void Playback::init_playback(k4n::playback::Sensor& sensor){
  //---------------------------

  //Init playback object
  std::string path = sensor.data.path.build();
  if(path == "") return;
  sensor.device.playback = k4a::playback::open(path.c_str());

  //Check validity
  if(!sensor.device.playback){
    std::cout<<"[error] Kinect sensor playback init"<<std::endl;
  }

  //---------------------------
}
void Playback::find_timestamp(k4n::playback::Sensor& sensor){
  //---------------------------

  sensor.timestamp.begin = find_mkv_ts_beg(sensor.data.path.build());
  sensor.timestamp.end = find_mkv_ts_end(sensor.data.path.build());
  sensor.timestamp.duration = sensor.timestamp.end - sensor.timestamp.begin;

  //---------------------------
}
void Playback::close_playback(k4n::playback::Sensor& sensor){
  //---------------------------

  sensor.device.playback.close();

  //---------------------------
}

//Subfunction
float Playback::find_mkv_ts_beg(std::string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_BEGIN);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_next_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_beg = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_beg;
}
float Playback::find_mkv_ts_end(std::string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_END);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_previous_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_end = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_end;
}

}
