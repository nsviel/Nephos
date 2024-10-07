#pragma once

#include <Utility/Namespace.h>
#include <memory>


namespace k4n::str::infra{

struct Texture{
  //---------------------------

  std::shared_ptr<utl::base::Image> image = std::make_shared<utl::base::Image>("Intensity");
  std::shared_ptr<utl::base::Depth> depth = std::make_shared<utl::base::Depth>("intensity_raw");

  //---------------------------
};

}
