#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Structure;}
namespace rad{class Node;}
namespace ope::fitting{class Polyfit;}
namespace ope::fitting{class Surface;}


namespace rad::model{

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

  //Subfunction
  void build_model();
  float apply_model(float x, float y);
  float compute_model_rmse();
  bool is_ready();

private:
  rad::Structure* rad_struct;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
