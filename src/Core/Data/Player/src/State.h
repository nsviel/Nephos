#pragma once

#include <Data/Base/Sensor/State.h>
#include <Data/Base/Sensor/Timestamp.h>

namespace dat::ply{class Node;}
namespace dat::ply{class Structure;}
namespace dat::gph{class Selection;}
namespace dat::base{class Set;}


namespace dat::ply{

class State
{
public:
  //Constructor / Destructor
  State(dat::ply::Node* node_player);
  ~State();

public:
  //Main function
  void loop();
  void reset();

  //State function
  void manage_state(dat::base::Set* set);
  void manage_update(dat::base::Set* set);
  void manage_restart(dat::base::Set* set);
  void manage_reset(dat::base::Set* set);
  void manage_query(dat::base::Set* set, float value);

public:
  dat::ply::Structure* ply_struct;
  dat::gph::Selection* gph_selection;
};

}
