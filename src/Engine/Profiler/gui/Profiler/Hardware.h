#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace prf::base{class Profiler;}
namespace prf::hardware{class Profiler;}
namespace utl::implot{class Plot;}


namespace prf::gui{

class Hardware
{
public:
  //Constructor / Destructor
  Hardware(prf::Node* node_profiler);
  ~Hardware();

public:
  //Main function
  void show_profiler(prf::base::Profiler* profiler);

  //Tab function

private:
  utl::implot::Plot* gui_plot;
  prf::hardware::Profiler* prf_temp;
};

}
