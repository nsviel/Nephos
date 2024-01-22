#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>

#include <Utility/Specific/common.h>
#include <Utility/Base/Entity/Namespace.h>

namespace k4n::dev{
class Sensor;


class Master : public utl::type::Set
{
public:
  //Constructor / Destructor
  Master();
  ~Master();

public:
  //Main function
  void insert_sensor_playback(k4n::dev::Sensor* sensor);
  void insert_sensor_capture(k4n::dev::Sensor* sensor);

  //Player function
  void update_player();
  void set_play();
  void set_pause(bool value);
  void set_desired_timestamp(float value);
  void set_stop();
  void set_restart();
  void set_record();
  void manage_restart();

public:
  list<k4n::dev::Sensor*> list_sensor;
  k4n::structure::Player player;
  k4n::structure::Operation operation;
  k4n::structure::Recorder recorder;

private:

};

}
