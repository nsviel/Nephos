#pragma once

#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Utility/Specific/common.h>

namespace k4n::dev{class Sensor;}
namespace k4n::structure{class Player;}
namespace k4n::structure{class Operation;}
namespace k4n::structure{class Recorder;}


namespace k4n::dev{

class Master : public utl::type::Set
{
public:
  //Constructor / Destructor
  Master();
  ~Master();

public:
  //Main function
  void insert_sensor(k4n::dev::Sensor* sensor);
  void reset();

  //Master function
  void manage_restart();
  void manage_forward();
  void manage_suppression(k4n::dev::Sensor* sensor);
  void manage_resynchronization();

  //Player function
  void player_update();
  void player_play();
  void player_pause(bool value);
  void player_query_ts(float value);
  void player_stop();
  void player_restart();
  void player_record();

  //Subfunction
  void visibility_normal();

public:
  k4n::structure::Player player;
  k4n::structure::Operation operation;
  k4n::structure::Recorder recorder;

private:

};

}
