#pragma once

#include <Profiler/src/Profiler/Base/Profiler.h>

namespace prf::base{class Profiler;}
namespace utl::hardare{class CPU;}
namespace utl::hardare{class Nvidia;}


namespace prf::hardware{

class Profilerold : public prf::base::Profiler
{
public:
  //Constructor / Destructor
  Profilerold();
  ~Profilerold();

public:
  //Main function
  void update_tic();

  //Subfunction

private:
  utl::hardare::CPU* rnd_cpu;
  utl::hardare::Nvidia* rnd_gpu;
};

}
