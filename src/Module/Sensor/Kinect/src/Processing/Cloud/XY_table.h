#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}


namespace k4n::processing::cloud{

class XY_table
{
public:
  //Constructor / Destructor
  XY_table(k4n::Node* node_k4n);
  ~XY_table();

public:
  //Main function
  void retrieve_table_xy(k4n::base::Sensor* sensor);

private:
};

}