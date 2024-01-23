#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Base/Entity/Namespace.h>
#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>

class K4A_capture;
class K4A_playback;
class Engine;

namespace k4n::dev{
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

  inline entity::Object* get_object(){return object;}
  inline utl::type::Data* get_data(){return object->data;}
  inline utl::type::Pose* get_pose(){return object->pose;}

public:
  entity::Object* object;
  k4n::dev::Master* master;

  k4n::structure::Param param;
  k4n::structure::Synchro synchro;
  k4n::structure::Recorder recorder;

  k4n::structure::Color color;
  k4n::structure::Depth depth;
  k4n::structure::Infrared ir;
  k4n::structure::IMU imu;

private:
  Engine* engine;
  eng::scene::Scene* sce_scene;
  eng::scene::Glyph* sce_glyph;
  eng::ope::Transformation* ope_transform;
  K4A_capture* k4a_capture;
  K4A_playback* k4a_playback;
};

}
