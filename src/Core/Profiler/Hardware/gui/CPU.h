#pragma once

namespace prf::hardware{class Node;}
namespace prf::hardware{class Structure;}
namespace prf::hardware{class Manager;}


namespace prf::gui::hardware{

class CPU
{
public:
  //Constructor / Destructor
  CPU(prf::hardware::Node* node_hardware);
  ~CPU();

public:
  //Main function
  void draw_tab();

  //Subfunction
  void draw_cpu_info();

private:
  prf::hardware::Structure* prf_struct;
  prf::hardware::Manager* prf_manager;
};

}
