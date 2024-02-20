#pragma once

#include <Profiler/src/Profiler/Profiler.h>
#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::scene{class Scene;}
namespace eng::scene{class Glyph;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::thread{class Capture;}
namespace k4n::thread{class Playback;}
namespace k4n::structure{class Param;}
namespace k4n::structure{class Synchro;}
namespace k4n::structure{class Recorder;}
namespace k4n::structure{class Color;}
namespace k4n::structure{class Depth;}
namespace k4n::structure{class Infrared;}
namespace k4n::structure{class IMU;}
namespace k4n::structure{class Image;}
namespace prf{class Profiler;}


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
  void reset_entity();
  void visibility_entity(bool value);

  //Capture function
  void run_capture();
  void run_playback(string path);
  void stop_threads();
  void reset_color_configuration();

  inline utl::entity::Object* get_object(){return &object;}
  inline utl::type::Data* get_data(){return object.data;}
  inline utl::type::Pose* get_pose(){return object.pose;}

public:
  prf::Profiler* profiler;
  k4n::dev::Master* master;

  utl::entity::Object object;
  k4n::structure::Image image;

  k4n::structure::Param param;
  k4n::structure::Synchro synchro;
  k4n::structure::Recorder recorder;

  k4n::structure::Color color;
  k4n::structure::Depth depth;
  k4n::structure::Infrared ir;
  k4n::structure::IMU imu;

private:
  eng::Node* node_engine;
  eng::scene::Scene* sce_scene;
  eng::scene::Glyph* sce_glyph;
  k4n::thread::Capture* k4n_capture;
  k4n::thread::Playback* k4n_playback;
};

}
