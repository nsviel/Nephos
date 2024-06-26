#pragma once

#include <Profiler/src/Profiler/Structure.h>

namespace prf{class Structure;}
namespace utl::hardare{class CPU;}
namespace utl::hardare{class Nvidia;}


namespace prf::hardware{

class Profiler : public prf::Structure
{
public:
  //Constructor / Destructor
  Profiler();
  ~Profiler();

public:
  //Main function
  void update_tic();

  //Subfunction

private:
  utl::hardare::CPU* rnd_cpu;
  utl::hardare::Nvidia* rnd_gpu;
};

}
