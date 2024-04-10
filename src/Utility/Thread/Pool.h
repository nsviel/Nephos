#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace eng::thread{class Thread;}


namespace eng::thread{

class Pool
{
public:
  //Constructor / Destructor
  Pool(eng::Node* node_engine);
  ~Pool();

public:
  //Main function
  void init();
  void clean();

private:
  vector<eng::thread::Thread> vec_thread;

  bool running;
  int size;
};


}
