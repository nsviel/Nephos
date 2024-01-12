#pragma once

#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Engine/Capture/K4N/Device/K4A_device.h>
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
  void play(K4A_device* k4a_device);
  void pause(K4A_device* k4a_device);
  void stop(K4A_device* k4a_device);
  void restart(K4A_device* k4a_device);
  void record(K4A_device* k4a_device);

private:
  eng::ope::Transformation* ope_transform;
  eng::ope::Attribut* ope_attribut;
  eng::ope::Operation* ope_operation;
};

}
