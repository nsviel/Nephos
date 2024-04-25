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
  //Measure function
  void import_measure();
  void export_measure();
  void clear_measure();
  void find_measure_bound();

  //Plot function
  void init_plot();
  void reset_plot();
  void update_plot();
  void clear_plot();

private:
  k4n::structure::K4N* k4n_struct;
};

}
