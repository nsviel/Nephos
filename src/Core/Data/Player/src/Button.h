#pragma once

#include <Data/Base/Sensor/State.h>
#include <Data/Base/Sensor/Timestamp.h>

namespace dat::ply{class Node;}
namespace dat::ply{class State;}
namespace dat::gph{class Selection;}
namespace dat::gph{class Element;}
namespace dat::base{class Set;}


namespace dat::ply{

class Player
{
public:
  //Constructor / Destructor
  Player(dat::ply::Node* node_player);
  ~Player();

public:
  //Main function
  void button_query(float value);
  void button_play();
  void button_pause();
  void button_stop();
  void button_replay();
  void button_record();
  void button_lock(bool value);
  void button_close();
  void button_forward(float value);

public:
  dat::gph::Selection* gph_selection;
  dat::gph::Element* gph_element;

  dat::ply::State* ply_state;
  dat::base::Timestamp timestamp;
  dat::base::State state;
};

}
