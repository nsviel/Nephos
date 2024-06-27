#pragma once

#include <Utility/Base/Type/Node.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace dat{class Node;}
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

  inline rad::correction::Node* get_node_correction(){return node_correction;}
  inline rad::calibration::Node* get_node_calibration(){return node_calibration;}

private:
  //Dependancy
  eng::Node* node_engine;
  dat::Node* node_data;
  prf::Node* node_profiler;

  //Child
  rad::correction::Node* node_correction;
  rad::calibration::Node* node_calibration;
  rad::gui::Panel* gui_panel;
};

}
