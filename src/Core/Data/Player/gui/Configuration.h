#pragma once

namespace utl::base{class Element;}
namespace dat::base{class Sensor;}


namespace dat::ply::gui{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration();
  ~Configuration();

  //Main function
  void design_configuration(std::shared_ptr<utl::base::Element> element);

  //Subfunction
  void sensor_config(std::shared_ptr<dat::base::Sensor> sensor);

private:

};

}
