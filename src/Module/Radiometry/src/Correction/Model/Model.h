#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace ope::fitting{class Polyfit;}
namespace ope::fitting{class Surface;}


namespace rad::correction{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::correction::Node* node_correction);
  ~Model();

public:
  //Main function
  void init();
  void compute_model();
  void clear_model();

  //Subfunction
  float apply_model(float x, float y);
  float rmse_model();
  bool is_model_build();
  void find_model_bound();
  void build_model();
  void update_model();

private:
  rad::correction::Structure* rad_struct;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
