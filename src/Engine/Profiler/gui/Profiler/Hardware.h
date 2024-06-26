#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/gui/Profiler/Structure/Profiler.h>

namespace prf{class Node;}
namespace prf::hardware{class Profiler;}
namespace utl::implot{class Plot;}


namespace prf::gui{

class Hardware : public prf::gui::Profiler
{
public:
  //Constructor / Destructor
  Hardware(prf::Node* node_profiler);
  ~Hardware();

public:
  //Main function
  void show_profiler(prf::hardware::Profiler* temperature);

  //Tab function

private:
  utl::implot::Plot* gui_plot;
  prf::hardware::Profiler* prf_temp;
};

}
