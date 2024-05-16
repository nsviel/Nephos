#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
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
  void draw_calibration_tab();

  //Subfunction
  void parameter_measure();
  void parameter_model();

  //Plot function
  void plot_measure_IfR(float height);
  void plot_measure_IfIt(float height);
  void plot_model_heatmap(float height);

private:
  rad::Model* rad_model;
  rad::model::Measure* rad_measure;
  rad::Structure* rad_struct;
  utl::implot::Plot* utl_plot;
};

}
