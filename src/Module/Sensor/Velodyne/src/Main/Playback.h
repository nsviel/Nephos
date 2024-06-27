#pragma once

namespace vld::structure{class Main;}
namespace vld::thread{class Playback;}


namespace vld::main{

class Playback
{
public:
  //Constructor / Destructor
  Playback(vld::structure::Main* vld_struct);
  ~Playback();

public:
  //Main function
  void start_playback();
  void stop_playback();

private:
  vld::structure::Main* vld_struct;
  vld::thread::Playback* thread_playback = nullptr;
};

}
