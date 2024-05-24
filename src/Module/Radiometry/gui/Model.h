#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::model{class Manager;}
namespace rad::model{class Measure;}
namespace rad::model{class Model;}
namespace rad::model{class Plot;}
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
  void draw_tab();

  //Subfunction
  void parameter_measure();
  void parameter_model();

  //Plot function
  void plot_measure_IfR(float height);
  void plot_measure_IfIt(float height);
  void plot_model_heatmap(float height);

private:
  rad::model::Manager* rad_manager;
  rad::model::Measure* rad_measure;
  rad::model::Model* rad_model;
  rad::model::Plot* rad_plot;
  rad::Structure* rad_struct;
  utl::implot::Plot* utl_plot;
};

}
