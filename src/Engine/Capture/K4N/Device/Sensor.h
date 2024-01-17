#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Base/Type/Namespace.h>
#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>

class K4A_capture;
class K4A_playback;
class Engine;

namespace k4n::dev{
class Master;


class Sensor : public entity::Entity, public k4n::dev::Device
{
public:
  //Constructor / Destructor
  Sensor(Engine* engine);
  ~Sensor();

public:
  //Main function
  void init();
  void reset();
  void destroy();

  //Player functions
  void set_play();

  //Entity function
  void update_entity();
  void remove_entity();
  void reset_entity();
  void visibility_entity(bool value);

  //Capture function
  void run_capture();
  void restart_capture();
  void run_playback(string path);
  void stop_threads();
  void reset_color_configuration();

  inline k4n::structure::Cloud* get_cloud(){return &cloud;}
  inline entity::Object* get_object(){return object;}
  inline utl::base::Data* get_data(){return object->data;}
  inline void set_pause(bool value){player.pause = value;}
  inline void set_desired_timestamp(float value){player.ts_seek = value;}

public:
  Engine* engine;
  eng::scene::Scene* eng_scene;
  eng::scene::Glyph* sce_glyph;
  eng::ope::Transformation* ope_transform;
  K4A_capture* k4a_capture;
  K4A_playback* k4a_playback;

  entity::Object* object;

  k4n::dev::Master* master;
  k4n::structure::Cloud cloud;
  k4n::structure::Device device;
  k4n::structure::Synchro synchro;

  k4n::structure::Color color;
  k4n::structure::Depth depth;
  k4n::structure::Infrared ir;
  k4n::structure::IMU imu;
};

}
