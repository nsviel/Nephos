#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>
#include <Engine/Scene/Data/Scene.h>
#include <Utility/Specific/common.h>

namespace k4n::dev{


class Connection
{
public:
  //Constructor / Destructor
  Connection(k4n::dev::Swarm* k4n_swarm);
  ~Connection();

public:
  //Main function
  void refresh_connected_sensor();

  //Subfunction
  void manage_new_dev(int number);
  void manage_less_dev(int number);

private:
  k4n::dev::Swarm* k4n_swarm;

  int nb_dev = 0;
};

}
