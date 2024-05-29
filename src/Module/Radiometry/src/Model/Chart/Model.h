#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Structure;}
namespace rad{class Node;}


namespace rad::model::chart{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::Node* node_radio);
  ~Model();

public:
  //Main function
  void import_model();
  void export_model();
  void compute_model();

  //Subfunction
  void build_model();

private:
  rad::Structure* rad_struct;
};

}
