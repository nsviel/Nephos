#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::gui{class Player;}
namespace k4n::structure{class K4N;}
namespace k4n::calibration{class Calibration;}
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
  void draw_calibration_player(k4n::dev::Sensor* sensor);
  void draw_calibration_tab(k4n::dev::Sensor* sensor);
  void draw_calibration_parameter(k4n::dev::Sensor* sensor);

  //Subfunction
  void plot_IfR(k4n::dev::Sensor* sensor, float height);
  void plot_IfIt(k4n::dev::Sensor* sensor, float height);
  void plot_IfItR(k4n::dev::Sensor* sensor, float height);

private:
  k4n::gui::Player* gui_player;
  k4n::calibration::Calibration* k4n_calibration;
  k4n::structure::K4N* k4n_struct;
  utl::implot::Plot* utl_plot;
};

}
