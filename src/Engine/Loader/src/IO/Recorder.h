#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace utl::base{class Data;}
namespace ldr::base{class Recorder;}


namespace ldr::io{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(ldr::Node* node_loader);
  ~Recorder();

public:
  //Main functions
  void insert_recorder(ldr::base::Recorder* recorder);

private:
  std::vector<ldr::base::Recorder*> vec_recorder;
};

}
