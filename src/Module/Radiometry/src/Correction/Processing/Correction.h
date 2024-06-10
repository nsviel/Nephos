#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::model{class Node;}
namespace rad::model::sphere{class Model;}
namespace dyn::base{class Sensor;}


namespace rad::correction{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::Node* node_radio);
  ~Correction();

public:
  //Main function
  void make_image_correction(dyn::base::Sensor* sensor, utl::media::Image* ir, utl::media::Image* depth);

  //Subfunction
  float apply_correction(float I_raw, float R, float It);

private:
  rad::Structure* rad_struct;
  rad::model::Node* node_model;
  rad::model::sphere::Model* rad_model;
};

}
