#pragma once

#include <Utility/Base/Class/Node.h>

namespace eng::trf{class Transformation;}
namespace eng::trf::gui{class Panel;}


namespace eng::trf{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  void init();
  void gui();

private:
  eng::trf::Transformation* trf_io;
  eng::trf::gui::Panel* gui_transformation;
};

}
