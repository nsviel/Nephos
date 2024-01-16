#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Specific/common.h>


namespace k4n::utils{

class Player
{
public:
  //Constructor / Destructor
  Player();
  ~Player();

public:
  //Main function
  void play(k4n::Sensor* k4n_sensor);
  void pause(k4n::Sensor* k4n_sensor);
  void stop(k4n::Sensor* k4n_sensor);
  void restart(k4n::Sensor* k4n_sensor);
  void record(k4n::Sensor* k4n_sensor);

private:
  eng::ope::Transformation* ope_transform;
  eng::ope::Attribut* ope_attribut;
  eng::ope::Operation* ope_operation;
};

}
