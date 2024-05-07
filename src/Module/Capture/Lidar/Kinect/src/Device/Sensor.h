#pragma once

#include <Data/Namespace.h>
#include <Dynamic/src/Base/Device.h>
#include <Utility/Specific/Common.h>
#include <Kinect/src/Structure/Namespace.h>

namespace eng{class Node;}
namespace dat{class Entity;}
namespace dat{class Set;}
namespace dat{class Glyph;}
namespace dat{class Graph;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::processing{class Data;}
namespace k4n::utils{class Configuration;}
namespace k4n::capture{class Sensor;}
namespace k4n::playback{class Sensor;}
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
namespace dat::base{class Object;}
namespace k4n::gui{class Sensor;}


namespace k4n::dev{

class Sensor : public dyn::base::Device
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
  void remove();
  void set_visibility(bool value);

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
  virtual void manage_reset();

  inline dat::base::Object* get_object(){return &object;}
  inline utl::type::Data* get_data(){return &object.data;}
  inline utl::type::Pose* get_pose(){return &object.pose;}
  inline bool is_thread_running(){return thread_running;}
  inline bool is_thread_paused(){return thread_paused;}

public:
  prf::graph::Profiler* profiler;
  k4n::dev::Master* master;
  k4n::gui::Sensor* gui_sensor;
  k4n::processing::Data* k4n_data;
  k4n::utils::Configuration* k4n_config;

  dat::base::Object object;
  k4n::structure::Image image;
  k4n::structure::Param param;
  k4n::structure::Color color;
  k4n::structure::Depth depth;
  k4n::structure::Infrared ir;
  k4n::structure::IMU imu;

protected:
  eng::Node* node_engine;
  dat::Entity* dat_entity;
  dat::Set* dat_set;
  dat::Glyph* dat_glyph;
  dat::Graph* dat_graph;

  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
  bool thread_paused = false;
};

}
