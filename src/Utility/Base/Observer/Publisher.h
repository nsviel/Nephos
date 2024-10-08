#pragma once

#include <list>

namespace utl::base{class Subscriber;}


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
  std::list<utl::base::Subscriber> list_subscriber;
};

}
