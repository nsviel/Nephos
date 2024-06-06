#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace utl::base{class Data;}
namespace ldr::base{class Recorder;}


namespace ldr::io{

class Saver
{
public:
  //Constructor / Destructor
  Saver(ldr::Node* node_loader);
  ~Saver();

public:
  //Main functions
  void insert_recorder(ldr::base::Recorder* recorder);

private:
  std::vector<ldr::base::Recorder*> vec_recorder;
};

}
