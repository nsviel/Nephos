#pragma once

namespace utl::base{class Element;}
namespace dyn::prc::base{class Sensor;}


namespace dat::ply::gui{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration();
  ~Configuration();

  //Main function
  void design_configuration(utl::base::Element* element);

  //Subfunction
  void sensor_config(dyn::base::Sensor* sensor);

private:

};

}
