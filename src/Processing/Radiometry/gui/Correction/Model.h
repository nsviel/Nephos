#pragma once

namespace rad{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Node;}
namespace rad::correction{class Measure;}
namespace rad::correction{class Model;}
namespace rad::correction{class Plot;}
namespace rad::correction::io{class Measure;}
namespace rad::correction::io{class Model;}
namespace utl::implot{class Plot;}
namespace dyn::base{class Sensor;}


namespace rad::gui::correction{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::Node* node_radio);
  ~Model();

public:
  //Main function
  void draw_tab(dyn::base::Sensor* sensor);

  //Subfunction
  void parameter_measure(dyn::base::Sensor* sensor);
  void parameter_model(dyn::base::Sensor* sensor);

  //Sphere plot function
  void plot_measure_IfR(float height);
  void plot_measure_IfIt(float height);
  void plot_model_heatmap(dyn::base::Sensor* sensor, float height);

private:
  rad::correction::Node* node_correction;
  rad::correction::Measure* rad_measure;
  rad::correction::Model* rad_model;
  rad::correction::Plot* rad_plot;
  rad::correction::Structure* rad_struct;
  rad::correction::io::Measure* rad_io_measure;
  rad::correction::io::Model* rad_io_model;
  utl::implot::Plot* utl_plot;
};

}
