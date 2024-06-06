#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace dat{class Node;}
namespace dyn{class Node;}
namespace rad{class Structure;}
namespace rad::detection{class Manager;}
namespace rad::model::sphere{class Manager;}
namespace rad::correction{class Manager;}
namespace rad::gui{class Panel;}


namespace rad{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
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
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}

  inline rad::Structure* get_rad_struct(){return rad_struct;}
  inline rad::detection::Manager* get_rad_detection(){return rad_detection;}
  inline rad::model::sphere::Manager* get_rad_model(){return rad_model;}
  inline rad::correction::Manager* get_rad_correction(){return rad_correction;}

private:
  //Dependancy
  eng::Node* node_engine;
  dat::Node* node_data;
  prf::Node* node_profiler;
  dyn::Node* node_dynamic;

  //Child
  rad::Structure* rad_struct;
  rad::detection::Manager* rad_detection;
  rad::model::sphere::Manager* rad_model;
  rad::correction::Manager* rad_correction;
  rad::gui::Panel* gui_panel;
};

}
