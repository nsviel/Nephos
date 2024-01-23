#pragma once

#include <Utility/Base/GUI/Panel.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>


namespace eng::k4n::gui{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(eng::k4n::Node* node_kinect);
  ~Recorder();

  //Main function
  void show_sensor_recorder();

  //Subfunction
  void recorder_path();

private:
  eng::k4n::Node* node_kinect;
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
