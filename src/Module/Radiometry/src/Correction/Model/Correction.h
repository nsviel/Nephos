#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Node;}
namespace rad::correction{class Model;}
namespace rad::correction::io{class Model;}
namespace dyn::base{class Sensor;}
namespace dat{class Image;}
namespace dat{class Selection;}


namespace rad::correction{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::correction::Node* node_correction);
  ~Correction();

public:
  //Main function
  void make_image_correction(dyn::base::Sensor* sensor, utl::media::Image* ir);

  //Subfunction
  void make_correction(dyn::base::Sensor* sensor, utl::media::Image* ir, std::vector<uint8_t>& vec_data);
  void update_correction_image(dyn::base::Sensor* sensor, utl::media::Image* ir, std::vector<uint8_t>& vec_data);
  float apply_correction(float I_raw, float R, float It);

private:
  dat::Image* dat_image;
  dat::Selection* dat_selection;
  rad::correction::Structure* rad_struct;
  rad::correction::Model* rad_model;
  rad::correction::io::Model* rad_io_model;
};

}
