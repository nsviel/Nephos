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
  //Main function
  void import_measure();
  void export_measure();
  void clear_measure();
  void plot_measure();

  //Subfunction
  void find_measure_bound();

  //Plot function
  void init_plot_data();
  void update_plot_data();
  void clear_plot_data();

private:
  rad::Structure* rad_struct;
};

}
