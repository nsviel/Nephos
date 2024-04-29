#pragma once

#include <Utility/Specific/Common.h>

namespace radio{class Structure;}


namespace radio::model{

class Measure
{
public:
  //Constructor / Destructor
  Measure(radio::Structure* radio_struct);
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
  radio::Structure* radio_struct;
};

}
