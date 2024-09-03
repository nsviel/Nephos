#pragma once

#include <Data/Sensor/Structure/State.h>
#include <Data/Sensor/Structure/Timestamp.h>

namespace dat::ply{class Node;}
namespace dat::ply{class State;}
namespace dat::ply{class Structure;}
namespace dat::gph{class Selection;}
namespace dat::gph{class Element;}


namespace dat::ply{

class Slider
{
public:
  //Constructor / Destructor
  Slider(dat::ply::Node* node_player);
  ~Slider();

public:
  //Main function
  void slider_query(float value);
  void slider_hold(float value);

public:
  dat::gph::Selection* gph_selection;
  dat::ply::Structure* ply_struct;
  dat::ply::State* ply_state;
};

}
