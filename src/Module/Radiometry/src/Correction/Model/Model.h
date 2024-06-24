#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace ope::fitting{class Polyfit;}
namespace ope::fitting{class Surface;}
namespace dyn::base{class Model;}
namespace dyn::base{class Sensor;}


namespace rad::correction{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::correction::Node* node_correction);
  ~Model();

public:
  //Main function
  void compute_model(dyn::base::Sensor* sensor);
  void clear_model();

  //Subfunction
  void build_model(dyn::base::Sensor* sensor);
  void update_model(dyn::base::Sensor* sensor);
  void find_model_bound(dyn::base::Sensor* sensor);
  float rmse_model(dyn::base::Sensor* sensor);
  float apply_model(float x, float y);

  //Checker function
  dyn::base::Model* get_model(dyn::base::Sensor* sensor, std::string depth_mode);
  bool is_model_build(dyn::base::Sensor* sensor);
  bool is_model_loaded(dyn::base::Sensor* sensor);

private:
  rad::correction::Structure* rad_struct;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
