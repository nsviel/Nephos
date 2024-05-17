#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace mod{class Node;}
namespace eng{class Node;}
namespace dat{class Node;}
namespace rad{class Structure;}
namespace rad{class Detection;}
namespace rad{class Model;}
namespace rad::detection{class Identification;}
namespace rad::detection{class Hough;}
namespace rad::detection{class Ransac;}
namespace rad::model{class Measure;}
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
  inline rad::Detection* get_rad_detection(){return rad_detection;}
  inline rad::Model* get_rad_model(){return rad_model;}

  inline rad::detection::Identification* get_rad_identification(){return rad_identification;}
  inline rad::detection::Hough* get_rad_hough(){return rad_hough;}
  inline rad::detection::Ransac* get_rad_ransac(){return rad_ransac;}
  inline rad::model::Measure* get_model_measure(){return rad_measure;}


private:
  //Dependancy
  eng::Node* node_engine;
  dat::Node* node_data;
  prf::Node* node_profiler;

  //Child
  rad::Structure* rad_struct;
  rad::Detection* rad_detection;
  rad::Model* rad_model;
  rad::detection::Identification* rad_identification;
  rad::detection::Hough* rad_hough;
  rad::detection::Ransac* rad_ransac;
  rad::model::Measure* rad_measure;
  rad::gui::Panel* gui_panel;
};

}
