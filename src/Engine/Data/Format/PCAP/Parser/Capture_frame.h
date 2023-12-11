#pragma once

#include <Utility/Base/Struct_file.h>
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
  bool build_frame(utility::base::File* cloud);
  void reset_frame();

  //Subfunctions
  void add_cloudsToFrame(utility::base::File* cloud);
  void end_cloudsToFrame(utility::base::File* cloud, int index);

  inline utility::base::File* get_endedFrame(){return frame_ended;}

private:
  utility::base::File* frame_onrun;
  utility::base::File* frame_ended;
};
