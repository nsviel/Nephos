#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace utl::base{class Data;}
namespace ldr::base{class Playback;}


namespace ldr::io{

class Playback
{
public:
  //Constructor / Destructor
  Playback(ldr::Node* node_loader);
  ~Playback();

public:
  //Main functions
  void insert_playback(ldr::base::Playback* playback);

private:
  std::vector<ldr::base::Playback*> vec_playback;
};

}
