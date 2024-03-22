#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class K4N;}
namespace utl::implot{class Plot;}


namespace k4n::gui{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(k4n::Node* node_k4n);
  ~Calibration();

public:
  //Main function
  void draw_calibration(k4n::dev::Sensor* sensor);

  //Subfunction
  void model_parameter(k4n::dev::Sensor* sensor);
  void plot_IfR(k4n::dev::Sensor* sensor);

private:
  k4n::structure::K4N* k4n_struct;
  utl::implot::Plot* utl_plot;
};

}
