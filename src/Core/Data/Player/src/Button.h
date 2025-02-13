#pragma once

#include <Data/Sensor/Structure/State.h>
#include <Data/Sensor/Structure/Timestamp.h>

namespace dat::ply{class Node;}
namespace dat::ply{class State;}
namespace dat::ply{class Structure;}
namespace dat::gph{class Selection;}
namespace dat::gph{class Element;}


namespace dat::ply{

class Button
{
public:
  //Constructor / Destructor
  Button(dat::ply::Node* node_player);
  ~Button();

public:
  //Main function
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
  dat::ply::Structure* ply_struct;
  dat::ply::State* ply_state;

  dat::sensor::Timestamp timestamp;
};

}
