#pragma once

#include <Utility/Specific/Common.h>

namespace vld{class Node;}
namespace vld::structure{class Main;}
namespace vld::thread{class Server;}
namespace vld::thread{class Screenshot;}


namespace vld::main{

class Capture
{
public:
  //Constructor / Destructor
  Capture(vld::Node* node_vld);
  ~Capture();

public:
  //Main functions
  void init();
  void clean();

private:
  vld::structure::Main* vld_struct;
  vld::thread::Server* thread_server;
  vld::thread::Screenshot* thread_screenshot;
};

}
