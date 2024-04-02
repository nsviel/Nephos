#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}


namespace k4n::calibration{

class Measure
{
public:
  //Constructor / Destructor
  Measure(k4n::Node* node_k4n);
  ~Measure();

public:
  //Main function
  void init();
  void import();
  void export();
  void update();

  //Subfunction
  void find_bounds();

private:
  k4n::structure::K4N* k4n_struct;
};

}
