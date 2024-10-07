#pragma once

#include <Utility/Namespace.h>
#include <memory>


namespace k4n::str::color{

struct Texture{
  //---------------------------

  std::shared_ptr<utl::base::Image> image = std::make_shared<utl::base::Image>("Color");
  std::shared_ptr<utl::base::Storage> table_xy = std::make_shared<utl::base::Storage>("color_table_xy");

  //---------------------------
};

}
