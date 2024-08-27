#pragma once

#include <Kinect/src/Structure/Buffer.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace k4n::structure{class Buffer;}
namespace k4n::processing::cloud{class XY_table;}
namespace utl::base{class Data;}
namespace dat::atr{class Field;}
namespace dat::atr{class Location;}


namespace k4n::processing::cloud{

class Data
{
public:
  //Constructor / Destructor
  Data(k4n::Node* node_k4n);
  ~Data();

public:
  //Main function
  void extract_data(std::shared_ptr<k4n::base::Sensor> sensor);

  //Subfunction
  bool check_condition(std::shared_ptr<k4n::base::Sensor> sensor);
  void extraction_init(std::shared_ptr<k4n::base::Sensor> sensor);
  void extraction_data(std::shared_ptr<k4n::base::Sensor> sensor);
  void extraction_transfer(std::shared_ptr<k4n::base::Sensor> sensor);

  //Data function
  void retrieve_location(std::shared_ptr<k4n::base::Sensor> sensor, int i);
  void retrieve_color(std::shared_ptr<k4n::base::Sensor> sensor, int i);
  void retrieve_ir(std::shared_ptr<k4n::base::Sensor> sensor, int i);

private:
  k4n::Structure* k4n_struct;
  k4n::processing::cloud::XY_table* k4n_xytable;
  k4n::structure::Buffer buffer;
  dat::atr::Field* atr_field;
  dat::atr::Location* atr_location;
};

}
