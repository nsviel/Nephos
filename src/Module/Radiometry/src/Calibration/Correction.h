#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::model{class Model;}


namespace rad{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::Node* node_radio);
  ~Correction();

public:
  //Main function
  void apply_correction(utl::media::Image* ir, utl::media::Image* depth);

  //Subfunction
  void compute_normal(utl::media::Image* depth);

private:
  rad::Structure* rad_struct;
  rad::model::Model* rad_model;
};

}
