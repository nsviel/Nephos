#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace utl::base{class Element;}


namespace dyn::gui{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration(dyn::Node* node_dynamic);
  ~Configuration();

  //Main function
  void design_configuration(utl::base::Element* element);

  //Subfunction
  void sensor_config(utl::base::Element* element);
  
private:

};

}
