#pragma once

#include <Utility/Specific/Common.h>

namespace radio{class Structure;}
namespace k4n::dev{class Sensor;}
namespace ope::fitting{class Polyfit;}
namespace ope::fitting{class Surface;}


namespace radio{

class Model
{
public:
  //Constructor / Destructor
  Model(radio::Structure* radio_struct);
  ~Model();

public:
  //Main function
  void import_model();
  void export_model();
  void compute_model();

  //Subfunction
  void make_model();
  float apply_model(float x, float y);
  float validation_model();
  void draw_model();

private:
  radio::Structure* radio_struct;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
