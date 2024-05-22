#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::model{class Model;}
namespace dat::base{class Sensor;}
namespace ope::normal{class KNN;}


namespace rad{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::Node* node_radio);
  ~Correction();

public:
  //Main function
  void apply_correction(dat::base::Sensor* sensor, utl::media::Image* ir, utl::media::Image* depth);

  //Subfunction
  void compute_normal(dat::base::Sensor* sensor, utl::media::Image* depth, vector<glm::vec3>& vec_Nxyz);
  void compute_normal_pca(dat::base::Sensor* sensor, utl::media::Image* depth, vector<glm::vec3>& vec_Nxyz);

private:
  rad::Structure* rad_struct;
  rad::model::Model* rad_model;
  ope::normal::KNN* ope_normal;
};

}
