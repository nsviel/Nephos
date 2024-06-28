#pragma once

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}


namespace dyn::element{

class Sensor
{
public:
  //Constructor / Destructor
  Sensor(dyn::Node* node_dynamic);
  ~Sensor();

public:
  //Main function


private:
  dyn::Structure* dyn_struct;
};

}
