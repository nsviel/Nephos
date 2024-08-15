#pragma once

namespace eng::trf{class Operation;}
namespace utl::base{class Element;}


namespace eng::trf::gui{

class Matrix
{
public:
  //Constructor / Destructor
  Matrix();
  ~Matrix();

public:
  //Main function
  void design_matrix(utl::base::Element* element);

  //Subfunction
  void draw_operation(utl::base::Element* element);
  void draw_matrix(utl::base::Element* element);

private:
  eng::trf::Operation* trf_operation;
};

}
