#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/gui/Profiler/Struct_profiler.h>

namespace prf{class Node;}
namespace prf::temp{class Profiler;}
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
  void draw_profiler(prf::temp::Profiler* temperature);

  //Tab function

private:
  utl::implot::Plot* gui_plot;
  prf::temp::Profiler* prf_temp;
};

}
