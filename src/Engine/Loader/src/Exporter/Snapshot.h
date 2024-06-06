#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace utl::base{class Data;}
namespace ldr::base{class Recorder;}


namespace ldr::io{

class Snapshot
{
public:
  //Constructor / Destructor
  Snapshot(ldr::Node* node_loader);
  ~Snapshot();

public:
  //Main functions
  void insert_recorder(ldr::base::Recorder* recorder);

private:
  std::vector<ldr::base::Recorder*> vec_recorder;
};

}
