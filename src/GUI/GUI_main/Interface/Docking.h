#pragma once

#include <Utility/UTL_specific/common.h>

class GUI;


namespace gui{

class Docking
{
public:
  //Constructor / Destructor
  Docking(GUI* gui);
  ~Docking();

public:
  //Main functions
  void docker_space_main();

private:
};

}
