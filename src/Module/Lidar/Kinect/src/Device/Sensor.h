#pragma once

#include <Data/Namespace.h>
#include <Utility/Specific/Common.h>
#include <Kinect/src/Structure/Namespace.h>

namespace eng{class Node;}
namespace dat{class Entity;}
namespace dat{class Set;}
namespace dat{class Glyph;}
namespace dat{class Graph;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::processing{class Image;}
namespace k4n::utils{class Configuration;}
namespace k4n::capture{class Sensor;}
namespace k4n::playback{class Sensor;}
namespace k4n::device{class Structure;}
namespace k4n::structure{class Playback;}
namespace k4n::structure{class Recorder;}
namespace k4n::color{class Structure;}
namespace k4n::depth{class Structure;}
namespace k4n::infrared{class Structure;}
namespace k4n::imu{class Structure;}
namespace k4n::structure{class Calibration;}
namespace k4n::structure{class FPS;}
namespace prf::graph{class Profiler;}
namespace dat::base{class Object;}
namespace k4n::gui{class Sensor;}


namespace k4n::dev{

class Sensor : public dat::base::Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n);
  ~Sensor();

public:
  //Main function
  void init();
  void info();
  void reset();
  void update_pose();
  void update_data();
  void remove();
  void set_visibility(bool value);
  vec3 convert_depth_2d_to_3d(ivec2 point_2d);

  //Init function
  void init_profiler();
  void init_image();
  void init_object();

  //Thread function
  void start_thread();
  void run_thread();
  void stop_thread();
  void wait_thread();

  //Subfunction
  virtual void thread_init(){}
  virtual void thread_loop(){}
  virtual void thread_end(){}
  virtual void manage_reset(){}

  inline dat::base::Object* get_object(){return &object;}
  inline utl::base::Data* get_data(){return &object.data;}
  inline utl::base::Pose* get_pose(){return &object.pose;}
  inline bool is_thread_running(){return thread_running;}
  inline bool is_thread_paused(){return thread_paused;}

public:
  prf::graph::Profiler* profiler;
  k4n::dev::Master* master;
  k4n::gui::Sensor* gui_sensor;
  k4n::processing::Image* k4n_image;
  k4n::utils::Configuration* k4n_config;

  dat::base::Object object;
  k4n::device::Structure device;
  k4n::color::Structure color;
  k4n::depth::Structure depth;
  k4n::infrared::Structure ir;
  k4n::imu::Structure imu;
  k4n::structure::FPS fps;

  float ts_beg = -1;
  float ts_end = -1;
  float ts_duration = -1;

protected:
  eng::Node* node_engine;
  dat::Entity* dat_entity;
  dat::Set* dat_set;
  dat::Glyph* dat_glyph;
  dat::Graph* dat_graph;

  std::thread thread;
  bool thread_running = false;
  bool thread_paused = false;
};

}
