#pragma once

#include <Utility/Namespace.h>
#include <memory>


namespace rlx::base{

struct Image{
  //---------------------------

  std::shared_ptr<utl::media::Image> color = std::make_shared<utl::media::Image>("Color");
  std::shared_ptr<utl::media::Image> depth = std::make_shared<utl::media::Image>("Depth");
  std::shared_ptr<utl::media::Image> infra = std::make_shared<utl::media::Image>("Intensity");

  //---------------------------
};

}
