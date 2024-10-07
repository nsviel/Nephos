#pragma once

#include <Utility/Namespace.h>
#include <memory>


namespace k4n::str::depth{

struct Texture{
  //---------------------------

  std::shared_ptr<utl::base::Image> image = std::make_shared<utl::base::Image>("Depth");
  std::shared_ptr<utl::base::Depth> depth = std::make_shared<utl::base::Depth>("depth_raw");
  std::shared_ptr<utl::base::Storage> table_xy = std::make_shared<utl::base::Storage>("depth_table_xy");

  //---------------------------
};

}
