#pragma once

#include <Utility/Base/Observer/Publisher.h>
#include <memory>

namespace utl::base{class Element;}


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
  void notify_selection(std::shared_ptr<utl::base::Element> element);

protected:
};

}
