#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}


namespace rad::model{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::Node* node_radio);
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
  rad::Structure* radio_struct;
};

}
