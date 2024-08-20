#pragma once

#include <string>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace ope::fitting{class Polyfit;}
namespace ope::fitting{class Surface;}
namespace dyn::prc::base{class Model;}
namespace dyn::prc::base{class Sensor;}


namespace rad::cor{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::cor::Node* node_correction);
  ~Model();

public:
  //Main function
  void compute_model(dyn::prc::base::Sensor* sensor);
  void clear_model();

  //Subfunction
  void build_model(dyn::prc::base::Sensor* sensor);
  void update_model(dyn::prc::base::Sensor* sensor);
  void find_model_bound(dyn::prc::base::Sensor* sensor);
  float rmse_model(dyn::prc::base::Sensor* sensor);
  float apply_model(float x, float y);

  //Checker function
  dyn::prc::base::Model* get_model(dyn::prc::base::Sensor* sensor, std::string depth_mode);
  bool is_model_build(dyn::prc::base::Sensor* sensor);
  bool is_model_loaded(dyn::prc::base::Sensor* sensor);

private:
  rad::cor::Structure* rad_struct;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
