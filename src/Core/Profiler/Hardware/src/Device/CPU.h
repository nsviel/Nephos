#pragma once

#include <vector>

namespace prf::hardware{class Node;}
namespace prf::hardware{class Structure;}
namespace sys::hardware{class CPU;}


namespace prf::hardware{

class CPU
{
public:
  //Constructor / Destructor
  CPU(prf::hardware::Node* node_hardware);
  ~CPU();

public:
  //Main function
  void collect_cpu_info();
  void collect_cpu_variable();

private:
  prf::hardware::Structure* prf_struct;
  sys::hardware::CPU* utl_cpu;
};

}
