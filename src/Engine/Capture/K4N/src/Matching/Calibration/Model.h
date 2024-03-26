#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace k4n::dev{class Sensor;}


namespace k4n::calibration{

class Model
{
public:
  //Constructor / Destructor
  Model(k4n::Node* node_k4n);
  ~Model();

public:
  //Main function
  void init_model();

  //Subfunction


private:
  k4n::structure::K4N* k4n_struct;
};

}
