#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, utl::base::Path path){
  //---------------------------

  this->k4n_image = new k4n::processing::Image(node_k4n);
  this->k4n_config = new k4n::utils::Configuration(node_k4n);
  this->gui_playback = new k4n::gui::Playback(node_k4n);

  this->file_size = utl::file::size(path.data);
  this->name = utl::path::get_name_from_path(path.data);
  this->data.path = path;
  this->data.name = utl::path::get_name_from_path(path.data);
  this->data.format = utl::path::get_format_from_path(path.data);
  this->data.topology.type = utl::topology::POINT;
  this->data.nb_data_max = 10000000;

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::info(){
  //---------------------------

  gui_playback->show_parameter(this);

  //---------------------------
}
void Sensor::thread_init(){
  //---------------------------

  //Init playback
  std::string& path = data.path.data;
  if(path == "") return;
  this->playback = k4a::playback::open(path.c_str());
  if(!playback){
    cout<<"[error] Sensor opening problem"<<endl;
    return;
  }

  k4n_config->find_playback_configuration(this);
  k4n_config->find_playback_calibration(this);
  k4n_config->make_transformation_from_calibration(this);

  //---------------------------
}
void Sensor::thread_loop(){
  prf::graph::Tasker* tasker = profiler.get_or_create_tasker("kinect::playback");
  //---------------------------

  tasker->loop_begin(30);

  //Next capture
  tasker->task_begin("capture");
  k4a::capture* capture = manage_new_capture();
  if(capture == nullptr) return;
  tasker->task_end("capture");

  //Wait previous threads to finish
  tasker->task_begin("wait");
  this->manage_old_capture(capture);
  tasker->task_end("wait");

  //Run processing
  k4n_image->start_thread(this);

  //Loop sleeping
  tasker->task_begin("pause");
  this->manage_pause();
  tasker->task_end("pause");

  tasker->loop_end();

  //---------------------------
}
void Sensor::thread_end(){
  //---------------------------

  k4n_image->wait_thread();
  this->playback.close();

  //---------------------------
}

//Subfunction
k4a::capture* Sensor::manage_new_capture(){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool capture_left = playback.get_next_capture(capture);
  if(capture_left == false){
    capture = nullptr;

    if(color.data.timestamp == timestamp.end){
      //player->manage_restart();
    }
  }

  //---------------------------
  return capture;
}
void Sensor::manage_old_capture(k4a::capture* capture){
  static std::queue<k4a::capture*> capture_queue;
  //---------------------------

  // Add the new capture to the queue
  capture_queue.push(capture);

  // Check if the queue size exceeds 5
  k4n_image->wait_thread();
  if(capture_queue.size() > 5){
    // Delete the oldest capture
    delete capture_queue.front();
    capture_queue.pop();
  }

  // Update the sensor parameter
  this->device.capture = capture;

  //---------------------------
}
void Sensor::manage_pause(){
/*  dyn::base::Player* player = &set_parent->player;
  //---------------------------

  //If pause, wait until end pause or end thread
  if(player->pause || !player->play){
    //Clear thread profiler and wait subthread fulfillment
    this->profiler.reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //Pause loop
    this->thread_paused = true;
    while(player->pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    this->thread_paused = false;
  }
*/
  //---------------------------
}
void Sensor::manage_ts_query(float value){
  //---------------------------

  auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
  playback.seek_timestamp(ts, K4A_PLAYBACK_SEEK_DEVICE_TIME);

  //---------------------------
}
vec3 Sensor::convert_depth_2d_to_3d(ivec2 point_2d){
  //---------------------------

  uint16_t* buffer = reinterpret_cast<uint16_t*>(depth.data.buffer);
  int width = depth.data.width;

  //Retrieve image coordinates
  int x = point_2d[0];
  int y = point_2d[1];
  k4a_float2_t source_xy = { static_cast<float>(x), static_cast<float>(y) };
  float source_z = static_cast<float>(buffer[y * width + x]);

  //Convert it into 3D coordinate
  k4a_float3_t target_xyz;
  bool success = device.calibration.convert_2d_to_3d(source_xy, source_z, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &target_xyz);
  vec4 xyzw = vec4(target_xyz.xyz.x, target_xyz.xyz.y, target_xyz.xyz.z, 1);

  //Apply transformation
  float inv_scale = 1.0f / 1000.0f;
  xyzw.x = -xyzw.x * inv_scale;
  xyzw.y = -xyzw.y * inv_scale;
  xyzw.z = xyzw.z * inv_scale;
  vec3 pose = vec3(xyzw.z, xyzw.x, xyzw.y);

  //---------------------------
  return pose;
}

}
