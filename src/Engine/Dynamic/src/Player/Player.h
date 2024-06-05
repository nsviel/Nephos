#pragma once

#include <Dynamic/src/Base/State.h>
#include <Dynamic/src/Base/Timestamp.h>
#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat{class Selection;}
namespace dat{class Set;}


namespace dyn::player{

class Player
{
public:
  //Constructor / Destructor
  Player(dyn::Node* node_dynamic);
  ~Player();

  //Main function
  void loop();
  void reset();

  //Player function
  void button_query(float value);
  void button_play();
  void button_pause();
  void button_stop();
  void button_restart();
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

  inline dyn::base::State* get_state(){return &state;}
  inline dyn::base::Timestamp* get_timestamp(){return &timestamp;}

public:
  dat::Selection* dat_selection;
  dat::Set* dat_set;

  dyn::base::Timestamp timestamp;
  dyn::base::State state;
};

}