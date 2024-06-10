#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::model{class Structure;}
namespace rad::model{class Node;}
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

  //Sphere plot function
  void plot_sphere();
  void plot_measure_IfR(float height);
  void plot_measure_IfIt(float height);
  void plot_model_heatmap(float height);

  //Chart plot function
  void plot_chart();

private:
  rad::model::Node* node_model;
  rad::model::sphere::Measure* rad_measure;
  rad::model::sphere::Model* rad_model;
  rad::model::sphere::Plot* rad_plot;
  rad::model::Structure* rad_struct;
  utl::implot::Plot* utl_plot;
};

}
