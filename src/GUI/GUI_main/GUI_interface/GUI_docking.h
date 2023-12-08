#pragma once

#include <UTL_specific/common.h>

class GUI;


namespace gui{

class GUI_docking
{
public:
  //Constructor / Destructor
  GUI_docking(GUI* gui);
  ~GUI_docking();

public:
  //Main functions
  void docker_space_main();

private:
};

}
