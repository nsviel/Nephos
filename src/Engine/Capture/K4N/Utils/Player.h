#pragma once

#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Engine/Capture/K4N/Namespace.h>
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
  void play(k4n::Device* k4a_device);
  void pause(k4n::Device* k4a_device);
  void stop(k4n::Device* k4a_device);
  void restart(k4n::Device* k4a_device);
  void record(k4n::Device* k4a_device);

private:
  eng::ope::Transformation* ope_transform;
  eng::ope::Attribut* ope_attribut;
  eng::ope::Operation* ope_operation;
};

}
