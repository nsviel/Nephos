#pragma once

#include <Utility/Base/Class/Panel.h>
#include <vector>
#include <string>


namespace utl::base{

class Subscriber
{
public:
  Subscriber();
  ~Subscriber();

public:
  //Main function
  virtual void update(){}

protected:

};

}
