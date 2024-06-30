#pragma once

#include <vector>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace utl::hardware{class CPU;}


namespace prf::hardware{

class CPU
{
public:
  //Constructor / Destructor
  CPU(prf::Node* node_profiler);
  ~CPU();

public:
  //Main function
  void collect_info();

  //Subfunction
  void collect_cpu_info();

private:
  prf::Structure* prf_struct;
  utl::hardware::CPU* utl_cpu;
};

}
