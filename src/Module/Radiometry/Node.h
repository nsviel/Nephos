#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace mod{class Node;}
namespace eng{class Node;}
namespace dat{class Node;}
namespace rad{class Structure;}
namespace rad{class Process;}
namespace rad{class Model;}
namespace rad::detection::image{class Detection;}
namespace rad::detection::image{class Hough;}
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
  inline rad::Process* get_rad_process(){return rad_process;}
  inline rad::Model* get_rad_model(){return rad_model;}

  inline rad::detection::image::Detection* get_rad_detection(){return rad_detection;}
  inline rad::detection::image::Hough* get_rad_hough(){return rad_hough;}
  inline rad::detection::Ransac* get_rad_ransac(){return rad_ransac;}
  inline rad::model::Measure* get_model_measure(){return rad_measure;}


private:
  //Dependancy
  eng::Node* node_engine;
  dat::Node* node_data;
  prf::Node* node_profiler;

  //Child
  rad::Structure* rad_struct;
  rad::Process* rad_process;
  rad::Model* rad_model;
  rad::detection::image::Detection* rad_detection;
  rad::detection::image::Hough* rad_hough;
  rad::detection::Ransac* rad_ransac;
  rad::model::Measure* rad_measure;
  rad::gui::Panel* gui_panel;
};

}
