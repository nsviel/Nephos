#pragma once

#include <Data/Sensor/Structure/State.h>
#include <Data/Sensor/Structure/Timestamp.h>
#include <memory>

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
  void manage_state(std::shared_ptr<dat::base::Set> set);
  void manage_update(std::shared_ptr<dat::base::Set> set);
  void manage_restart(std::shared_ptr<dat::base::Set> set);
  void manage_reset(std::shared_ptr<dat::base::Set> set);
  void manage_query(std::shared_ptr<dat::base::Set> set, float value);

public:
  dat::ply::Structure* ply_struct;
  dat::gph::Selection* gph_selection;
};

}
