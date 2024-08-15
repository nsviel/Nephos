#pragma once

#include <Utility/Base/Class/Node.h>

namespace eng{class Node;}
namespace dat{class Node;}

namespace eng::trf{class IO;}
namespace eng::trf::gui{class Panel;}


namespace eng::trf{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void gui();

  inline dat::Node* get_node_data(){return node_data;}
  inline eng::trf::IO* get_trf_io(){return trf_io;}

private:
  dat::Node* node_data;

  eng::trf::IO* trf_io;
  eng::trf::gui::Panel* gui_transformation;
};

}
