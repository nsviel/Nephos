#pragma once

#include <Engine/Capture/K4N/src/Device/Swarm.h>
#include <Engine/Capture/K4N/src/Device/Namespace.h>
#include <Utility/Specific/common.h>

namespace k4n::src::dev{
class Swarm;


class Connection
{
public:
  //Constructor / Destructor
  Connection(k4n::src::dev::Swarm* k4n_swarm);
  ~Connection();

public:
  //Main function
  void refresh_connected_dev();

  //Subfunction
  void manage_new_dev(int number);
  void manage_less_dev(int number);

private:
  k4n::src::dev::Swarm* k4n_swarm;

  int nb_dev = 0;
};

}
