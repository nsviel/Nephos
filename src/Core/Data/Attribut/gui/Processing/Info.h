#pragma once

#include <memory>

namespace utl::base{class Element;}


namespace dat::atr::gui{

class Info
{
public:
  //Constructor / Destructor
  Info();
  ~Info();

  //Main function
  void design_info(std::shared_ptr<utl::base::Element> element);

  //Subfunction
  void path_info(std::shared_ptr<utl::base::Element> element);

private:

};

}
