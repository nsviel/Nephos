#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Sensor;}
namespace k4n::gui{class Player;}
namespace radio{class Structure;}
namespace radio{class Detection;}
namespace radio{class Model;}
namespace radio::model{class Measure;}

namespace utl::implot{class Plot;}


namespace radio::gui{

class Model
{
public:
  //Constructor / Destructor
  Model(radio::Structure* radio_struct);
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
  radio::Model* radio_model;
  radio::model::Measure* radio_measure;
  radio::Structure* radio_struct;
  utl::implot::Plot* utl_plot;
};

}
