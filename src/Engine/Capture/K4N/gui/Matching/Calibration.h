#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::gui{class Player;}
namespace k4n::structure{class K4N;}
namespace k4n::calibration{class Calibration;}
namespace k4n::calibration{class Model;}
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
  void draw_calibration_measure(k4n::dev::Sensor* sensor);
  void draw_calibration_model(k4n::dev::Sensor* sensor);

  //Subfunction
  void draw_model(k4n::dev::Sensor* sensor);
  void draw_measure(k4n::dev::Sensor* sensor);
  void plot_measure_IfR(k4n::dev::Sensor* sensor, float height);
  void plot_measure_IfIt(k4n::dev::Sensor* sensor, float height);
  void plot_model_heatmap(k4n::dev::Sensor* sensor, float height);

private:
  k4n::gui::Player* gui_player;
  k4n::calibration::Calibration* k4n_calibration;
  k4n::calibration::Model* k4n_model;
  k4n::structure::K4N* k4n_struct;
  utl::implot::Plot* utl_plot;
};

}
