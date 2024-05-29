#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::model::sphere{class Manager;}
namespace rad::model::sphere{class Measure;}
namespace rad::model::sphere{class Model;}
namespace rad::model::sphere{class Plot;}
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
  rad::model::sphere::Manager* rad_manager;
  rad::model::sphere::Measure* rad_measure;
  rad::model::sphere::Model* rad_model;
  rad::model::sphere::Plot* rad_plot;
  rad::Structure* rad_struct;
  utl::implot::Plot* utl_plot;
};

}
