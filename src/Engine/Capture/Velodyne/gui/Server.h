#pragma once

#include <Utility/Specific/Common.h>

namespace vld::structure{class Main;}


namespace vld::gui{

class Server
{
public:
  //Constructor / Destructor
  Server(vld::structure::Main* vld_struct);
  ~Server();

public:
  //Main function
  void design_server();

private:
  vld::structure::Main* vld_struct;
};

}
