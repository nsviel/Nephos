#pragma once

#include <Utility/Base/Namespace.h>
#include <Utility/Function/Math/fct_math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <chrono>


class Capture_frame
{
public:
  //Constructor / Destructor
  Capture_frame();
  ~Capture_frame();

public:
  //Main functions
  bool build_frame(eng::base::File* cloud);
  void reset_frame();

  //Subfunctions
  void add_cloudsToFrame(eng::base::File* cloud);
  void end_cloudsToFrame(eng::base::File* cloud, int index);

  inline eng::base::File* get_endedFrame(){return frame_ended;}

private:
  eng::base::File* frame_onrun;
  eng::base::File* frame_ended;
};
