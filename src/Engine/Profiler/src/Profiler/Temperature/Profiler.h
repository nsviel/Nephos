#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/src/Profiler/Structure.h>

namespace prf{class Structure;}


namespace prf::temp{

class Profiler : public prf::Structure
{
public:
  //Constructor / Destructor
  Profiler();
  ~Profiler();

public:
  //Main function
  void reset();

  //Subfunction
  float find_CPU_temperature();
  float find_GPU_temperature();

private:

};

}
