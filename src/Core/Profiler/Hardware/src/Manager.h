#pragma once

namespace prf::hardware{class Node;}
namespace prf::hardware{class Structure;}
namespace prf::hardware{class CPU;}
namespace prf::hardware{class GPU;}


namespace prf::hardware{

class Manager
{
public:
  //Constructor / Destructor
  Manager(prf::hardware::Node* node_hardware);
  ~Manager();

public:
  //Main function
  void init();
  void loop();

private:
  prf::hardware::Structure* prf_struct;
  prf::hardware::CPU* cpu_device;
  prf::hardware::GPU* gpu_device;
};

}
