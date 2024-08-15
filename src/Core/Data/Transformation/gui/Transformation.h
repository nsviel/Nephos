#pragma once

namespace ope{class Operation;}
namespace utl::base{class Element;}


namespace dat::trf::gui{

class Transformation
{
public:
  //Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  //Main function
  void design_transformation(utl::base::Element* element);

  //Subfunction
  void draw_operation(utl::base::Element* element);
  void draw_matrix(utl::base::Element* element);

private:
  ope::Operation* ope_operation;
};

}
