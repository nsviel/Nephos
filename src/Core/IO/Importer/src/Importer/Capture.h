#pragma once

#include <memory>
#include <string>
#include <vector>

namespace io::imp{class Node;}
namespace io::imp{class Importer;}
namespace io::imp{class Operation;}


namespace io::imp{

class Capture
{
public:
  //Constructor / Destructor
  Capture(io::imp::Node* node_importer);
  ~Capture();

public:
  //Main function
  void run_capture(std::string& vendor, std::string& product);

private:
  io::imp::Importer* io_importer;
  io::imp::Operation* io_operation;
};

}
