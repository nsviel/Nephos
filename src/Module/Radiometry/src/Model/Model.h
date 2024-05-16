#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Structure;}
namespace rad{class Node;}
namespace ope::fitting{class Polyfit;}
namespace ope::fitting{class Surface;}


namespace rad{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::Node* node_radio);
  ~Model();

public:
  //Main function
  void import_model();
  void export_model();
  void compute_model();
  void draw_model();
  
  //Subfunction
  void make_model();
  float apply_model(float x, float y);
  float validation_model();

private:
  rad::Structure* rad_struct;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
