#pragma once

#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Utility/Base/Entity/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;
namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Master;}
namespace eng::k4n::thread{class K4A_capture;}
namespace eng::k4n::thread{class K4A_playback;}
namespace eng::k4n::structure{class Param;}
namespace eng::k4n::structure{class Synchro;}
namespace eng::k4n::structure{class Recorder;}
namespace eng::k4n::structure{class Color;}
namespace eng::k4n::structure{class Depth;}
namespace eng::k4n::structure{class Infrared;}
namespace eng::k4n::structure{class IMU;}


namespace eng::k4n::dev{

class Sensor : public utl::type::Entity
{
public:
  //Constructor / Destructor
  Sensor(eng::k4n::Node* k4n_node);
  ~Sensor();

public:
  //Main function
  void init();
  void reset();

  //Entity function
  void update_entity();
  void remove_entity();
  void reset_entity();
  void visibility_entity(bool value);

  //Capture function
  void run_capture();
  void run_playback(string path);
  void stop_threads();
  void reset_color_configuration();

  inline utl::entity::Object* get_object(){return object;}
  inline utl::type::Data* get_data(){return object->data;}
  inline utl::type::Pose* get_pose(){return object->pose;}

public:
  utl::entity::Object* object;
  eng::k4n::dev::Master* master;

  eng::k4n::structure::Param param;
  eng::k4n::structure::Synchro synchro;
  eng::k4n::structure::Recorder recorder;

  eng::k4n::structure::Color color;
  eng::k4n::structure::Depth depth;
  eng::k4n::structure::Infrared ir;
  eng::k4n::structure::IMU imu;

private:
  Engine* engine;
  eng::scene::Scene* sce_scene;
  eng::scene::Glyph* sce_glyph;
  eng::ope::Transformation* ope_transform;
  eng::k4n::thread::K4A_capture* k4a_capture;
  eng::k4n::thread::K4A_playback* k4a_playback;
};

}
