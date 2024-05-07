#pragma once

#include <Data/src/Base/Entity.h>
#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}


namespace dyn::base{

class Device : public dat::base::Entity
{
public:
  //Constructor / Destructor
  Device();
  ~Device();

public:
  //Main function
  virtual void init(){}
  virtual void info(){}
  virtual void reset(){}

protected:

};


}
