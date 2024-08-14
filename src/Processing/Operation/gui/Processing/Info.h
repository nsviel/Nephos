#pragma once

namespace utl::base{class Element;}


namespace ope::gui{

class Info
{
public:
  //Constructor / Destructor
  Info();
  ~Info();

  //Main function
  void design_info(utl::base::Element* element);

  //Subfunction
  void path_info(utl::base::Element* element);

private:

};

}
