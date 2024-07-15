#pragma once

#include <string>
#include <vector>

namespace io{class Node;}
namespace io{class Structure;}
namespace dat::base{class Entity;}


namespace io::exporter{

class Operation
{
public:
  //Constructor / Destructor
  Operation(io::Node* node_io);
  ~Operation();

public:
  //Main function
  void make_operation(dat::base::Entity* entity);

  //Subfunction
  void make_transformation(dat::base::Entity* entity);

private:
  io::Structure* io_struct;
};

}
