#pragma once

#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Utility/Specific/common.h>

namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::structure{class Player;}
namespace eng::k4n::structure{class Operation;}
namespace eng::k4n::structure{class Recorder;}


namespace eng::k4n::dev{

class Master : public utl::type::Set
{
public:
  //Constructor / Destructor
  Master();
  ~Master();

public:
  //Main function
  void insert_sensor_playback(eng::k4n::dev::Sensor* sensor);
  void insert_sensor_capture(eng::k4n::dev::Sensor* sensor);
  void delete_sensor(eng::k4n::dev::Sensor* sensor);
  void delete_all_sensor();
  void delete_selected_sensor();
  void reset();

  //Player function
  void player_update();
  void player_play();
  void player_pause(bool value);
  void player_query_ts(float value);
  void player_stop();
  void player_restart();
  void player_record();
  void manage_restart();
  void manage_forward();

public:
  list<eng::k4n::dev::Sensor*> list_sensor;
  eng::k4n::structure::Player player;
  eng::k4n::structure::Operation operation;
  eng::k4n::structure::Recorder recorder;
  eng::k4n::structure::Voxel voxel;

private:

};

}
