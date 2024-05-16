#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::gui{class Player;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad{class Detection;}
namespace rad{class Model;}
namespace rad::model{class Measure;}
namespace utl::implot{class Plot;}


namespace rad::gui{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(rad::Node* node_radio);
  ~Calibration();

public:
  //Main function
  void draw_calibration_player();
  void draw_calibration_tab();
  void draw_calibration_measure();
  void draw_calibration_model();

  //Subfunction
  void draw_measure();
  void plot_measure_IfR(float height);
  void plot_measure_IfIt(float height);
  void plot_model_heatmap(float height);

private:
  k4n::gui::Player* gui_player;
  rad::Detection* rad_detection;
  rad::Model* rad_model;
  rad::model::Measure* rad_measure;
  rad::Structure* rad_struct;
  utl::implot::Plot* utl_plot;
};

}
