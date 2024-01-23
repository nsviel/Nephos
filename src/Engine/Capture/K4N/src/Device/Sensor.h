#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Utility/Base/Entity/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Utility/Specific/common.h>

class K4A_capture;
class K4A_playback;
class Engine;

namespace k4n::src::dev{
class Master;


class Sensor : public utl::type::Entity
{
public:
  //Constructor / Destructor
  Sensor(Engine* engine);
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
  k4n::src::dev::Master* master;

  k4n::src::str::Param param;
  k4n::src::str::Synchro synchro;
  k4n::src::str::Recorder recorder;

  k4n::src::str::Color color;
  k4n::src::str::Depth depth;
  k4n::src::str::Infrared ir;
  k4n::src::str::IMU imu;

private:
  Engine* engine;
  eng::scene::Scene* sce_scene;
  eng::scene::Glyph* sce_glyph;
  ope::src::Transformation* ope_transform;
  K4A_capture* k4a_capture;
  K4A_playback* k4a_playback;
};

}
