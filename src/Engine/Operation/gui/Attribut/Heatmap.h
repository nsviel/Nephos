#pragma once

namespace ope{class Node;}
namespace ope{class Structure;}
namespace ope::color{class Routine;}
namespace utl::base{class Element;}
namespace dat::base{class Entity;}


namespace ope::gui{

class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap(ope::Node* node_dynamic);
  ~Heatmap();

public:
  //Main function
  void heatmap_mode(utl::base::Element* element);

private:
  ope::Structure* ope_struct;
  ope::color::Routine* ope_colorizer;
};

}
