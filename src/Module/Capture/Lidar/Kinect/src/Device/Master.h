#pragma once

#include <Data/src/Base/Set.h>
#include <Utility/Specific/Common.h>
#include <Kinect/src/Structure/Master/Namespace.h>

namespace dat{class Set;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::config{class Configuration;}
namespace k4n::structure{class Player;}
namespace k4n::structure{class Operation;}
namespace k4n::structure{class Recorder;}
namespace k4n::structure{class Configuration;}


namespace k4n::dev{
enum Mode{
  CAPTURE = 0,
  PLAYBACK = 1,
};

class Master : public dat::base::Set
{
public:
  //Constructor / Destructor
  Master(k4n::Node* node_k4n);
  ~Master();

public:
  //Main function
  void insert_sensor(k4n::dev::Sensor* sensor);
  void reset();

  //Master function
  void manage_color_control();
  void manage_restart_thread();
  void manage_restart();
  void manage_forward();
  void manage_resynchronization();
  void manage_configuration();

  //Player function
  void player_update();
  void player_play();
  void player_pause(bool value);
  void player_query_ts(float value);
  void player_stop();
  void player_restart();
  void player_record();
  void player_close();

  //Subfunction
  void visibility_normal();

public:
  dat::Set* dat_set;
  k4n::config::Configuration* k4n_config;

  k4n::structure::Player player;
  k4n::structure::Operation operation;
  k4n::structure::Recorder recorder;
  k4n::structure::Configuration config;
  k4n::structure::Synchro synchro;

  int mode = k4n::dev::PLAYBACK;
};

}
