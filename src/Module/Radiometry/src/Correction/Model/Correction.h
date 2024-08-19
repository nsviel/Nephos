#pragma once

#include <stdint.h>
#include <vector>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Node;}
namespace rad::correction{class Model;}
namespace rad::correction::io{class Model;}
namespace dyn::prc::base{class Sensor;}
namespace dat::elm{class Image;}
namespace dat::gph{class Selection;}
namespace utl::media{class Image;}
namespace dat::atr{class Field;}


namespace rad::correction{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::correction::Node* node_correction);
  ~Correction();

public:
  //Main function
  void make_image_correction(dyn::prc::base::Sensor* sensor, utl::media::Image* ir);

  //Subfunction
  void make_correction(dyn::prc::base::Sensor* sensor, utl::media::Image* ir, std::vector<uint8_t>& vec_data);
  void update_correction_image(dyn::prc::base::Sensor* sensor, utl::media::Image* ir, std::vector<uint8_t>& vec_data);
  float apply_correction(float I_raw, float R, float It);

private:
  dat::elm::Image* dat_image;
  dat::gph::Selection* dat_selection;
  rad::correction::Structure* rad_struct;
  rad::correction::Model* rad_model;
  rad::correction::io::Model* rad_io_model;
  dat::atr::Field* atr_field;
};

}
