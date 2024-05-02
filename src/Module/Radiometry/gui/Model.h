#pragma once

#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}
namespace k4n::gui{class Player;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad{class Detection;}
namespace rad{class Model;}
namespace rad::model{class Measure;}

namespace utl::implot{class Plot;}


namespace rad::gui{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::Node* node_radio);
  ~Model();

public:
  //Main function
  void draw_calibration_player(dat::base::Sensor* sensor);
  void draw_calibration_tab(dat::base::Sensor* sensor);
  void draw_calibration_measure(dat::base::Sensor* sensor);
  void draw_calibration_model(dat::base::Sensor* sensor);

  //Subfunction
  void draw_measure(dat::base::Sensor* sensor);
  void plot_measure_IfR(dat::base::Sensor* sensor, float height);
  void plot_measure_IfIt(dat::base::Sensor* sensor, float height);
  void plot_model_heatmap(dat::base::Sensor* sensor, float height);

private:
  k4n::gui::Player* gui_player;
  rad::Detection* radio_detection;
  rad::Model* radio_model;
  rad::model::Measure* radio_measure;
  rad::Structure* radio_struct;
  utl::implot::Plot* utl_plot;
};

}
