#pragma once

#include <Utility/Base/Data/Data.h>
#include <glm/glm.hpp>
#include <vector>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace k4n::processing::cloud{class XY_table;}
namespace utl::base{class Data;}


namespace k4n::processing::cloud{

class Data
{
public:
  //Constructor / Destructor
  Data(k4n::Node* node_k4n);
  ~Data();

public:
  //Main function
  void extract_data(k4n::base::Sensor* sensor);

  //Subfunction
  bool check_condition(k4n::base::Sensor* sensor);
  void extraction_init(k4n::base::Sensor* sensor);
  void extraction_data(k4n::base::Sensor* sensor);
  void extraction_transfer(k4n::base::Sensor* sensor);

  //Data function
  void retrieve_location(k4n::base::Sensor* sensor, int i);
  void retrieve_color(k4n::base::Sensor* sensor, int i);
  void retrieve_ir(k4n::base::Sensor* sensor, int i);

private:
  k4n::Structure* k4n_struct;
  k4n::processing::cloud::XY_table* k4n_xytable;
  utl::base::Data buffer_data;
};

}
