#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace k4n::dev{class Sensor;}
namespace ope::fitting{class Polyfit;}


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

  //Measure function
  void import_measure();
  void export_measure();
  void update_plot();
  void find_model_bounds();

private:
  k4n::structure::K4N* k4n_struct;
  ope::fitting::Polyfit* ope_polyfit;
};

}
