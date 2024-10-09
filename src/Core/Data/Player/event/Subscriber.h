#pragma once

#include <Utility/Base/Observer/Subscriber.h>
#include <memory>

namespace dat::ply{class Node;}
namespace utl::base{class Element;}


namespace dat::gph{

class Subscriber : public utl::base::Subscriber
{
public:
  Subscriber(dat::ply::Node* node_player);
  ~Subscriber();

public:
  //Main function
  void subscribe();

protected:
};

}
