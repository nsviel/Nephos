#pragma once

#include <Utility/Base/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Base/Entity/Struct_entity.h>


namespace k4n::dev{

struct Device{
  //---------------------------

  virtual void set_play(){}
  virtual void set_pause(bool value){}
  virtual void set_stop(){}
  virtual void set_restart(){}
  virtual void set_record(){}
  virtual void set_desired_timestamp(float value){}

  k4n::structure::Player player;
  k4n::structure::Recorder recorder;
  k4n::structure::Playback playback;

  string device_type = "";

  //---------------------------
};

}
