#pragma once

namespace ope{class Node;}
namespace ope{class Structure;}
namespace dat::base{class Entity;}
namespace dat::base{class Set;}
namespace utl::base{class Element;}
namespace ope::color{class Colorizer;}


namespace ope::color{

class Routine
{
public:
  //Constructor / Destructor
  Routine(ope::Node* node_operation);
  ~Routine();

public:
  //Main function
  void colorize_element(utl::base::Element* element);

  //Subfunction
  void colorize_set(dat::base::Set* set);
  void colorize_entity(dat::base::Entity* entity);

private:
  ope::Structure* ope_struct;
  ope::color::Colorizer* ope_colorizer;
};

}
