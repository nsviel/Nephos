#pragma once

#include <Profiler/src/Hardware/Structure/Queue.h>
#include <Profiler/src/Hardware/Structure/Structure.h>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::hardware{class CPU;}
namespace prf::hardware{class GPU;}


namespace prf::hardware{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(prf::Node* node_profiler);
  ~Profiler();

public:
  //Main function
  void init();
  void loop();

private:
  prf::Structure* prf_struct;
  prf::hardware::CPU* cpu_device;
  prf::hardware::GPU* gpu_device;
};

}
