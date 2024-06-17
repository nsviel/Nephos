#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Node;}
namespace rad::correction{class Model;}
namespace dyn::base{class Sensor;}
namespace dat{class Image;}


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
  dat::Image* dat_image;
  rad::correction::Structure* rad_struct;
  rad::correction::Model* model_sphere;
};

}
