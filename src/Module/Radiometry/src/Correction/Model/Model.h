#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Measure;}
namespace rad::correction{class Plot;}
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
  void build_model();

  //Subfunction
  float apply_model(float x, float y);
  float rmse_model();
  bool is_model_build();
  void find_model_bound();
  void compute_model();

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Measure* rad_measure;
  rad::correction::Plot* rad_plot;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
