#pragma once

namespace prf::hardware{class Node;}
namespace prf::hardware{class Structure;}
namespace prf::hardware{class Manager;}


namespace prf::gui::hardware{

class GPU
{
public:
  //Constructor / Destructor
  GPU(prf::hardware::Node* node_hardware);
  ~GPU();

public:
  //Main function
  void draw_tab();

  //Subfunction
  void draw_gpu_info();
  void draw_gpu_queue();

private:
  prf::hardware::Structure* prf_struct;
  prf::hardware::Manager* prf_manager;
};

}
