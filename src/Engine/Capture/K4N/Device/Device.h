#pragma once

#include <Utility/Base/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Base/Entity/Struct_entity.h>


namespace k4n::dev{

struct Device : public entity::Entity{
  //---------------------------

  virtual void set_pause(bool value){}

  k4n::structure::Player player;
  k4n::structure::Recorder recorder;
  k4n::structure::Playback playback;

  //---------------------------
};

}
