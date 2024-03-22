#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}


namespace k4n::gui{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(k4n::Node* node_k4n);
  ~Calibration();

public:
  //Main function

private:
  k4n::structure::K4N* k4n_struct;
};

}
