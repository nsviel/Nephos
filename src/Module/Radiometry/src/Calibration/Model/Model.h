#pragma once

#include <Utility/Specific/Common.h>

namespace rad::model{class Structure;}
namespace rad::model{class Node;}


namespace rad::calibration{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::model::Node* node_model);
  ~Model();

public:
  //Main function
  void import_model();
  void export_model();
  void compute_model();

  //Subfunction
  void build_model();

private:
  rad::model::Structure* rad_struct;
};

}
