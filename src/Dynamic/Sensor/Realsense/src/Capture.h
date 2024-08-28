#pragma once

namespace rlx{class Node;}
namespace rlx{class Structure;}


namespace rlx{

class Capture
{
public:
  //Constructor / Destructor
  Capture(rlx::Node* node_realsense);
  ~Capture();

public:
  //Main function
  void capture();

private:
  rlx::Structure* rlx_struct;
};

}
