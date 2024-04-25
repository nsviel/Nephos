#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::gui{class Player;}
namespace k4n::structure{class K4N;}
namespace radio{class Detection;}
namespace radio::calibration{class Measure;}
namespace radio::calibration{class Model;}
namespace utl::implot{class Plot;}


namespace radio::gui{

class Model
{
public:
  //Constructor / Destructor
  Model(k4n::Node* node_k4n);
  ~Model();

public:
  //Main function
  void draw_calibration_player(k4n::dev::Sensor* sensor);
  void draw_calibration_tab(k4n::dev::Sensor* sensor);
  void draw_calibration_measure(k4n::dev::Sensor* sensor);
  void draw_calibration_model(k4n::dev::Sensor* sensor);

  //Subfunction
  void draw_measure(k4n::dev::Sensor* sensor);
  void plot_measure_IfR(k4n::dev::Sensor* sensor, float height);
  void plot_measure_IfIt(k4n::dev::Sensor* sensor, float height);
  void plot_model_heatmap(k4n::dev::Sensor* sensor, float height);

private:
  k4n::gui::Player* gui_player;
  radio::Detection* radio_detection;
  radio::calibration::Measure* k4n_measure;
  radio::calibration::Model* k4n_model;
  k4n::structure::K4N* k4n_struct;
  utl::implot::Plot* utl_plot;
};

}
