#pragma once

#include <memory>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Model;}
namespace dat::base{class Sensor;}


namespace rad::cor{

class IfRIt
{
public:
  //Constructor / Destructor
  IfRIt(rad::cor::Node* node_correction);
  ~IfRIt();

public:
  //Main function
  void init();
  void update(dat::base::Sensor& sensor);
  void reset();

private:
  rad::cor::Structure* rad_struct;
  rad::cor::Model* rad_model;
};

}
