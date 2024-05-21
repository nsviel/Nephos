#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace mod{class Node;}
namespace eng{class Node;}
namespace dat{class Node;}
namespace rad{class Structure;}
namespace rad::detection::image{class Detection;}
namespace rad::detection::cloud{class Detection;}
namespace rad::model{class Model;}
namespace rad::model{class Measure;}
namespace rad::model{class Plot;}
namespace rad::gui{class Panel;}


namespace rad{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(mod::Node* node_module);
  ~Node();

public:
  //Main function
  void config();
  void init();
  void loop();
  void gui();
  void clean();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline dat::Node* get_node_data(){return node_data;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline rad::Structure* get_rad_struct(){return rad_struct;}
  inline rad::detection::image::Detection* get_image_detection(){return rad_image_detection;}
  inline rad::detection::cloud::Detection* get_cloud_detection(){return rad_cloud_detection;}
  inline rad::model::Model* get_rad_model(){return rad_model;}
  inline rad::model::Measure* get_model_measure(){return rad_measure;}
  inline rad::model::Plot* get_model_plot(){return rad_plot;}

private:
  //Dependancy
  eng::Node* node_engine;
  dat::Node* node_data;
  prf::Node* node_profiler;

  //Child
  rad::Structure* rad_struct;
  rad::detection::image::Detection* rad_image_detection;
  rad::detection::cloud::Detection* rad_cloud_detection;
  rad::model::Model* rad_model;
  rad::model::Measure* rad_measure;
  rad::model::Plot* rad_plot;
  rad::gui::Panel* gui_panel;
};

}
