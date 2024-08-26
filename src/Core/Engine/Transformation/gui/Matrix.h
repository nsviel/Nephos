#pragma once

#include <memory>

namespace eng::trf{class Operation;}
namespace eng::trf{class Utils;}
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
  void design_matrix(std::shared_ptr<utl::base::Element> element);

  //Subfunction
  void draw_operation(std::shared_ptr<utl::base::Element> element);
  void draw_matrix(std::shared_ptr<utl::base::Element> element);

private:
  eng::trf::Operation* trf_operation;
  eng::trf::Utils* trf_utils;
};

}
