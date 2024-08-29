#pragma once

namespace vld{class Node;}
namespace vld{class Structure;}
namespace vld::thread{class Playback;}


namespace vld::main{

class Playback
{
public:
  //Constructor / Destructor
  Playback(vld::Node* node_velodyne);
  ~Playback();

public:
  //Main function
  void start_playback();
  void stop_playback();

private:
  vld::Structure* vld_struct;
  vld::thread::Playback* thread_playback = nullptr;
};

}
