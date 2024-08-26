#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Node;}
namespace rad::cor{class Model;}
namespace rad::cor::io{class Model;}
namespace dat::base{class Sensor;}
namespace dat::elm{class Image;}
namespace dat::gph{class Selection;}
namespace utl::media{class Image;}
namespace dat::atr{class Field;}


namespace rad::cor{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::cor::Node* node_correction);
  ~Correction();

public:
  //Main function
  void make_image_correction(std::shared_ptr<dat::base::Sensor> sensor, utl::media::Image* ir);

  //Subfunction
  void make_correction(std::shared_ptr<dat::base::Sensor> sensor, utl::media::Image* ir, std::vector<uint8_t>& vec_data);
  void update_correction_image(std::shared_ptr<dat::base::Sensor> sensor, utl::media::Image* ir, std::vector<uint8_t>& vec_data);
  float apply_correction(float I_raw, float R, float It);

private:
  dat::elm::Image* dat_image;
  dat::gph::Selection* gph_selection;
  rad::cor::Structure* rad_struct;
  rad::cor::Model* rad_model;
  rad::cor::io::Model* rad_io_model;
  dat::atr::Field* atr_field;
};

}
