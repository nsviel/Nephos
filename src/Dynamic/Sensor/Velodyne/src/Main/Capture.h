#pragma once

namespace vld{class Node;}
namespace vld{class Structure;}
namespace vld::thread{class Server;}


namespace vld::main{

class Capture
{
public:
  //Constructor / Destructor
  Capture(vld::Node* node_velodyne);
  ~Capture();

public:
  //Main function
  void init();
  void clean();

private:
  vld::Structure* vld_struct;
  vld::thread::Server* thread_server;
};

}
