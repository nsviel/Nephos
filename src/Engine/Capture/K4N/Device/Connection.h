#pragma once

#include <Engine/Capture/K4N/Device/Swarm.h>
#include <Engine/Capture/K4N/Device/Namespace.h>
#include <Utility/Specific/common.h>

namespace k4n::dev{
class Swarm;


class Connection
{
public:
  //Constructor / Destructor
  Connection(k4n::dev::Swarm* k4n_swarm);
  ~Connection();

public:
  //Main function
  void refresh_connected_dev();

  //Subfunction
  void manage_new_dev(int number);
  void manage_less_dev(int number);

private:
  k4n::dev::Swarm* k4n_swarm;

  int nb_dev = 0;
};

}
