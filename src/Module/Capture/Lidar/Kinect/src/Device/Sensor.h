#pragma once

#include <Scene/Namespace.h>
#include <Utility/Specific/Common.h>
#include <Kinect/src/Structure/Namespace.h>

namespace eng{class Node;}
namespace sce{class Entity;}
namespace sce{class Set;}
namespace gly{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::thread{class Capture;}
namespace k4n::thread{class Playback;}
namespace k4n::structure{class Param;}
namespace k4n::structure{class Playback;}
namespace k4n::structure{class Recorder;}
namespace k4n::structure{class Color;}
namespace k4n::structure{class Depth;}
namespace k4n::structure{class Infrared;}
namespace k4n::structure{class IMU;}
namespace k4n::structure{class Image;}
namespace k4n::structure{class Calibration;}
namespace prf::graph{class Profiler;}
namespace utl::entity{class Object;}


namespace k4n::dev{

class Sensor : public utl::type::Entity
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n);
  ~Sensor();

public:
  //Main function
  void init();
  void reset();

  //Entity function
  void update_pose();
  void remove_entity();
  void set_visibility(bool value);

  //Capture function
  void run_thread_capture();
  void run_thread_playback(string path);
  void stop_threads();
  void wait_threads();
  void reset_color_configuration();

  bool is_capture_running();
  bool is_playback_running();
  bool is_playback_paused();

  inline utl::entity::Object* get_object(){return &object;}
  inline utl::type::Data* get_data(){return &object.data;}
  inline utl::type::Pose* get_pose(){return &object.pose;}

public:
  prf::graph::Profiler* profiler;
  k4n::dev::Master* master;

  utl::entity::Object object;
  k4n::structure::Image image;

  k4n::structure::Param param;
  k4n::structure::Playback playback;
  k4n::structure::Detection detection;

  k4n::structure::Color color;
  k4n::structure::Depth depth;
  k4n::structure::Infrared ir;
  k4n::structure::IMU imu;

private:
  eng::Node* node_engine;
  sce::Entity* sce_entity;
  sce::Set* sce_set;
  gly::Node* node_glyph;
  k4n::thread::Capture* k4n_capture;
  k4n::thread::Playback* k4n_playback;
  k4n::structure::K4N* k4n_struct;

  bool thread_running = false;
};

}
