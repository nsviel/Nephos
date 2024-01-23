#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;

namespace eng::k4n::dev{


class Recorder
{
public:
  //Constructor / Destructor
  Recorder(Engine* engine);
  ~Recorder();

public:
  //Main function


private:
  Engine* engine;

  string default_folder;
};

}
