#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/src/Profiler/Structure.h>

namespace prf{class Structure;}
namespace rnd::hardare{class CPU;}
namespace rnd::hardare{class Nvidia;}


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

private:
  rnd::hardare::CPU* rnd_cpu;
  rnd::hardare::Nvidia* rnd_gpu;
};

}
