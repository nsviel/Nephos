#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace k4n::dev{class Sensor;}
namespace ope::fitting{class Polyfit;}


namespace k4n::calibration{

class Model
{
public:
  //Constructor / Destructor
  Model(k4n::Node* node_k4n);
  ~Model();

public:
  //Main function
  void import_model();
  void export_model();
  void draw_model();

  //Subfunction
  void make_model();
  float apply_model(float x, float y);
  float validation_model();

private:
  k4n::structure::K4N* k4n_struct;
  ope::fitting::Polyfit* ope_polyfit;
};

}
