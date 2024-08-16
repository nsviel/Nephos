#pragma once

#include <Processing/src/Base/State.h>
#include <Processing/src/Base/Timestamp.h>

namespace dat::ply{class Node;}
namespace dat::gph{class Selection;}
namespace dat::elm{class Set;}


namespace dat::ply{

class Player
{
public:
  //Constructor / Destructor
  Player(dat::ply::Node* node_player);
  ~Player();

  //Main function
  void loop();
  void reset();

  //Player function
  void button_query(float value);
  void button_play();
  void button_pause();
  void button_stop();
  void button_replay();
  void button_record();
  void button_lock(bool value);
  void button_close();
  void button_forward(float value);

  //Subfunction
  void manage_state(dat::base::Set* set);
  void manage_update(dat::base::Set* set);
  void manage_restart(dat::base::Set* set);
  void manage_reset(dat::base::Set* set);
  void manage_query(dat::base::Set* set, float value);

  inline dyn::prc::base::State* get_state(){return &state;}
  inline dyn::prc::base::Timestamp* get_timestamp(){return &timestamp;}

public:
  dat::gph::Selection* dat_selection;
  dat::elm::Set* dat_set;

  dyn::prc::base::Timestamp timestamp;
  dyn::prc::base::State state;
};

}
