#pragma once

#include <memory>

namespace rad{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Node;}
namespace rad::cor{class Measure;}
namespace rad::cor{class Model;}
namespace rad::cor{class Plot;}
namespace rad::cor::io{class Measure;}
namespace rad::cor::io{class Model;}
namespace utl::implot{class Plot;}
namespace dat::base{class Sensor;}


namespace rad::cor::gui{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::Node* node_radio);
  ~Model();

public:
  //Main function
  void draw_tab(std::shared_ptr<dat::base::Sensor> sensor);

  //Subfunction
  void parameter_measure(std::shared_ptr<dat::base::Sensor> sensor);
  void parameter_model(std::shared_ptr<dat::base::Sensor> sensor);

  //Sphere plot function
  void plot_measure_IfR(float height);
  void plot_measure_IfIt(float height);
  void plot_model_heatmap(std::shared_ptr<dat::base::Sensor> sensor, float height);

private:
  rad::cor::Node* node_correction;
  rad::cor::Measure* rad_measure;
  rad::cor::Model* rad_model;
  rad::cor::Plot* rad_plot;
  rad::cor::Structure* rad_struct;
  rad::cor::io::Measure* rad_io_measure;
  rad::cor::io::Model* rad_io_model;
  utl::implot::Plot* utl_plot;
};

}
