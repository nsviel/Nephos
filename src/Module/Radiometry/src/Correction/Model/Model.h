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
  void import_model();
  void export_model();
  void compute_model();

  //Subfunction
  void build_model();
  float apply_model(float x, float y);
  float compute_model_rmse();
  bool is_ready();

  inline rad::correction::Structure* get_rad_struct(){return rad_struct;}
  inline rad::correction::Measure* get_rad_measure(){return rad_measure;}
  inline rad::correction::Plot* get_rad_plot(){return rad_plot;}

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Measure* rad_measure;
  rad::correction::Plot* rad_plot;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
