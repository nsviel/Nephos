#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace dat{class Node;}
namespace dyn{class Node;}
namespace rad{class Structure;}
namespace rad::detection{class Node;}
namespace rad::model{class Node;}
namespace rad::correction{class Node;}
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
  inline rad::detection::Node* get_node_detection(){return node_detection;}
  inline rad::model::Node* get_node_model(){return node_model;}
  inline rad::correction::Node* get_node_correction(){return node_correction;}

private:
  //Dependancy
  eng::Node* node_engine;
  dat::Node* node_data;
  prf::Node* node_profiler;
  dyn::Node* node_dynamic;

  //Child
  rad::Structure* rad_struct;
  rad::detection::Node* node_detection;
  rad::model::Node* node_model;
  rad::correction::Node* node_correction;
  rad::gui::Panel* gui_panel;
};

}
