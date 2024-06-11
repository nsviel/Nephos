#pragma once

#include <Utility/Specific/Common.h>

namespace rad::model{class Node;}
namespace rad::model{class Structure;}
namespace rad::model::sphere{class Measure;}
namespace rad::model::sphere{class Plot;}
namespace ope::fitting{class Polyfit;}
namespace ope::fitting{class Surface;}


namespace rad::model::sphere{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::model::Node* node_model);
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

  inline rad::model::Structure* get_rad_struct(){return rad_struct;}
  inline rad::model::sphere::Measure* get_rad_measure(){return rad_measure;}
  inline rad::model::sphere::Plot* get_rad_plot(){return rad_plot;}

private:
  rad::model::Structure* rad_struct;
  rad::model::sphere::Measure* rad_measure;
  rad::model::sphere::Plot* rad_plot;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
