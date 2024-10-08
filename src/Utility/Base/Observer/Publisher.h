#pragma once

#include <Utility/Base/Class/Panel.h>
#include <vector>
#include <string>


namespace utl::base{

class Publisher
{
public:
  Publisher();
  ~Publisher();

public:
  //Main function
  virtual void attach(){}
  virtual void detach(){}
  virtual void notify(){}
  
protected:

};

}
