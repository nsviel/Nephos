#pragma once

namespace dyn{class Node;}
namespace utl::base{class Element;}


namespace dyn::gui{

class Info
{
public:
  //Constructor / Destructor
  Info(dyn::Node* node_dynamic);
  ~Info();

  //Main function
  void design_info(utl::base::Element* element);

  //Subfunction
  void path_info(utl::base::Element* element);
  void sensor_info(utl::base::Element* element);
  void playback_info(utl::base::Element* element);

private:

};

}
