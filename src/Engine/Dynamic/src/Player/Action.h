#pragma once

#include <Dynamic/src/Player/State.h>
#include <Dynamic/src/Base/Timestamp.h>
#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat{class Selection;}
namespace dat::base{class Set;}
namespace dyn::base{class Timestamp;}


namespace dyn::player{

class Action
{
public:
  //Constructor / Destructor
  Action(dyn::Node* node_dynamic);
  ~Action();

  //Main function
  void player_play();
  void player_pause();
  void player_stop();
  void player_restart();
  void player_record();
  void player_lock(bool value);
  void player_close();

public:
  dat::Selection* dat_selection;

  dyn::base::Timestamp timestamp;
  dyn::player::State state;

  
  std::string time = "%";
  utl::base::Path path;
  float size = 0;
  int fps_cur = 0;
  int fps_qry = 0;
};

}
