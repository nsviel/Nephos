#pragma once

#include <Utility/Namespace.h>
#include <memory>


namespace rlx::base{

struct Image{
  //---------------------------

  std::shared_ptr<utl::base::Image> color = std::make_shared<utl::base::Image>("Color");
  std::shared_ptr<utl::base::Image> depth = std::make_shared<utl::base::Image>("Depth");
  std::shared_ptr<utl::base::Image> infra = std::make_shared<utl::base::Image>("Intensity");

  //---------------------------
};

}
