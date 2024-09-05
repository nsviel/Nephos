#pragma once

#include <memory>
#include <string>
#include <vector>

namespace dat::base{class Set;}
namespace dat::base{class Object;}
namespace utl::base{class Data;}
namespace utl::base{class Element;}
namespace utl::base{class Path;}
namespace utl::base{class Thread;}
namespace io::imp{class Node;}
namespace io::imp{class Structure;}
namespace io::imp{class Operation;}
namespace io::base{class Importer;}


namespace io::imp{

class Capture
{
public:
  //Constructor / Destructor
  Capture(io::imp::Node* node_importer);
  ~Capture();

public:
  //Main function


private:
  io::imp::Structure* io_struct;
  io::imp::Operation* io_operation;

  std::vector<io::base::Importer*> vec_importer;
};

}
