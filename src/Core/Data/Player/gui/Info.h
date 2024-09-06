#pragma once

#include <memory>

namespace utl::base{class Element;}


namespace dat::ply::gui{

class Info
{
public:
  //Constructor / Destructor
  Info();
  ~Info();

  //Main function
  void design_info(std::shared_ptr<utl::base::Element> element);
  void design_configuration(std::shared_ptr<utl::base::Element> element);

  //Subfunction
  void path_info(std::shared_ptr<utl::base::Element> element);
  void sensor_info(std::shared_ptr<utl::base::Element> element);

private:

};

}
