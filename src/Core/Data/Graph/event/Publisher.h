#pragma once

#include <Utility/Base/Observer/Publisher.h>
#include <list>


namespace dat::gph{

class Publisher : public utl::base::Publisher
{
public:
  Publisher();
  ~Publisher();

public:
  //Main function
  void attach(){}
  void detach(){}
  void notify(){}

protected:
};

}
