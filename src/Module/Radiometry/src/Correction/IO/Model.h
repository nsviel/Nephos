#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Model;}


namespace rad::correction::io{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::correction::Node* node_correction);
  ~Model();

public:
  //Main function
  void import_model();
  void export_model();

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Model* rad_model;
};

}
