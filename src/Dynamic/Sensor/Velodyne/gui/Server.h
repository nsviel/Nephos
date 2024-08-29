#pragma once

namespace vld{class Node;}
namespace vld{class Structure;}


namespace vld::gui{

class Server
{
public:
  //Constructor / Destructor
  Server(vld::Node* node_velodyne);
  ~Server();

public:
  //Main function
  void design_server();

private:
  vld::Structure* vld_struct;
};

}
