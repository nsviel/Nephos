#pragma once

#include <Engine/Base/Namespace.h>
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
  bool build_frame(eng::data::File* cloud);
  void reset_frame();

  //Subfunctions
  void add_cloudsToFrame(eng::data::File* cloud);
  void end_cloudsToFrame(eng::data::File* cloud, int index);

  inline eng::data::File* get_endedFrame(){return frame_ended;}

private:
  eng::data::File* frame_onrun;
  eng::data::File* frame_ended;
};
