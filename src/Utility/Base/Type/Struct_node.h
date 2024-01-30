#pragma once

#include <Utility/Specific/common.h>


namespace utl::type{

class Node
{
public:
  Node(){}
  ~Node(){}

public:
  //Main function
  virtual void init(){}
  virtual void loop(){}
  virtual void gui(){}
  virtual void reset(){}
  virtual void exit(){}
  virtual void wait(){}

private:

};

}
