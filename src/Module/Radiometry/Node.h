#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace dat{class Node;}
namespace dyn{class Node;}
namespace rad::correction{class Node;}
namespace rad::calibration{class Node;}
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

  inline rad::correction::Node* get_node_correction(){return node_correction;}
  inline rad::calibration::Node* get_node_calibration(){return node_calibration;}

private:
  //Dependancy
  eng::Node* node_engine;
  dat::Node* node_data;
  prf::Node* node_profiler;
  dyn::Node* node_dynamic;

  //Child
  rad::correction::Node* node_correction;
  rad::calibration::Node* node_calibration;
  rad::gui::Panel* gui_panel;
};

}
