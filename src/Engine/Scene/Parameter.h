#pragma once

#include <Utility/Specific/common.h>


namespace eng::scene{

struct Parameter : public utl::type::Parameter{
  //---------------------------

  vector<string> supported_format;

  //---------------------------
};

}
