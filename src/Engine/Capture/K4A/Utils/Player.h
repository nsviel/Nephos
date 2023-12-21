#pragma once

#include <Engine/Capture/K4A/Structure/Namespace.h>
#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <Utility/Specific/common.h>


namespace eng::kinect{

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
  void rotation(K4A_device* k4a_device, int value);

private:
  eng::ope::Transformation* ope_transform;
  eng::ope::Attribut* ope_attribut;
};

}
