#pragma once

namespace rad::calibration{class Structure;}
namespace rad::calibration{class Node;}


namespace rad::calibration{

class Model
{
public:
  //Constructor / Destructor
  Model(rad::calibration::Node* node_calibration);
  ~Model();

public:
  //Main function
  void import_model();
  void export_model();
  void compute_model();

  //Subfunction
  void build_model();

private:
  rad::calibration::Structure* rad_struct;
};

}
