#pragma once

namespace rad::cal{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal{class Plot;}


namespace rad::cal{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::cal::Node* node_calibration);
  ~Measure();

public:
  //Main function
  void import_measure();
  void export_measure();
  void clear_measure();

  //Subfunction
  void init();

private:
  rad::cal::Structure* rad_struct;
  rad::cal::Plot* rad_plot;
};

}
