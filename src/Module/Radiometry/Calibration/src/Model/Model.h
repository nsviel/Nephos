#pragma once

namespace rad::cal{class Structure;}
namespace rad::cal{class Node;}


namespace rad::cal{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::cal::Node* node_calibration);
  ~Model();

public:
  //Main function
  void import_model();
  void export_model();
  void compute_model();

  //Subfunction
  void build_model();

private:
  rad::cal::Structure* rad_struct;
};

}
