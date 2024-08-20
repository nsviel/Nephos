#pragma once

#include <string>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace ope::fitting{class Polyfit;}
namespace ope::fitting{class Surface;}
namespace dat::base{class Model;}
namespace dat::base{class Sensor;}


namespace rad::cor{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::cor::Node* node_correction);
  ~Model();

public:
  //Main function
  void compute_model(dat::base::Sensor* sensor);
  void clear_model();

  //Subfunction
  void build_model(dat::base::Sensor* sensor);
  void update_model(dat::base::Sensor* sensor);
  void find_model_bound(dat::base::Sensor* sensor);
  float rmse_model(dat::base::Sensor* sensor);
  float apply_model(float x, float y);

  //Checker function
  dat::base::Model* get_model(dat::base::Sensor* sensor, std::string depth_mode);
  bool is_model_build(dat::base::Sensor* sensor);
  bool is_model_loaded(dat::base::Sensor* sensor);

private:
  rad::cor::Structure* rad_struct;
  ope::fitting::Polyfit* ope_polyfit;
  ope::fitting::Surface* ope_surface;
};

}
