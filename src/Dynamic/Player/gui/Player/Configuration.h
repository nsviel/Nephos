#pragma once

namespace dyn{class Node;}
namespace utl::base{class Element;}
namespace dyn::base{class Sensor;}


namespace dyn::ply::gui{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration(dyn::Node* node_dynamic);
  ~Configuration();

  //Main function
  void design_configuration(utl::base::Element* element);

  //Subfunction
  void sensor_config(dyn::base::Sensor* sensor);

private:

};

}
