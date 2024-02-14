#pragma once

// Server side implementation of UDP client-server model

#include <Utility/Specific/common.h>
#include <thread>

class Node_interface;
class Extractor;

namespace velodyne{class Frame;}
namespace velodyne{class Server;}
namespace velodyne::parser{class VLP16;}


namespace velodyne{

class Capture
{
public:
  //Constructor / Destructor
  Capture(Node_interface* node_interface);
  ~Capture();

public:
  //Recording functions
  void start_watcher(int port);
  void stop_watcher();
  Cloud* get_obj_capture();

  //LiDAR function
  void lidar_start_motor();
  void lidar_stop_motor();
  void lidar_check_status();
  void lidar_check_connection();

  //LiDAR parametrization
  void lidar_set_rpm(int value);
  void lidar_set_cameraFOV_min(int fov_min);
  void lidar_set_cameraFOV_max(int fov_max);
  void lidar_set_cameraFOV(int min, int max);

  inline bool* get_is_newSubset(){return &is_newSubset;}
  inline bool* get_is_connected(){return &is_connected;}
  inline bool* get_is_rotating(){return &is_rotating;}
  inline bool* get_run_capture(){return &run_capture;}
  inline bool get_is_first_run(){return is_first_run;}
  inline int* get_capture_port(){return &capture_port;}
  inline int get_rot_freq(){return rot_freq;}
  inline int get_rot_rpm(){return rot_rpm;}
  inline int get_fov_min(){return fov_min;}
  inline int get_fov_max(){return fov_max;}
  inline float get_time_frame(){return time_frame;}
  inline float get_time_packet(){return time_packet;}
  inline string* get_lidar_ip(){return &lidar_ip;}

private:
  Extractor* extractManager;
  velodyne::Frame* velo_frame;
  velodyne::Server* velo_server;
  velodyne::parser::VLP16* parser_vlp16;

  Cloud* subset_capture;
  utl::media::File udp_capture;

  float time_frame;
  float time_packet;
  string lidar_ip;
  int rot_freq, rot_rpm;
  int fov_min, fov_max;
  int capture_port;
  bool is_newSubset;
  bool run_capture;
  bool is_rotating;
  bool is_connected;
  bool is_first_run;
  thread thread_capture;
};

}
