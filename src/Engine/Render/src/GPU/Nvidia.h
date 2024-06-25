#pragma once

#include <Utility/Specific/Common.h>


namespace prf::temp{

class Nvidia
{
public:
  //Constructor / Destructor
  Nvidia();
  ~Nvidia();

public:
  //Main function
  void reset();

  //Subfunction
  float find_CPU_temperature();
  float find_GPU_temperature();

private:

};

}
