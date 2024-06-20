#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}


namespace dyn::gui{

class Info
{
public:
  //Constructor / Destructor
  Info(dyn::Node* node_dynamic);
  ~Info();

  //Main function
  void design_info(utl::base::Element* element);

private:

};

}
