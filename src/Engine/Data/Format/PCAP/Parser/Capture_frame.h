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
  bool build_frame(util::base::File* cloud);
  void reset_frame();

  //Subfunctions
  void add_cloudsToFrame(util::base::File* cloud);
  void end_cloudsToFrame(util::base::File* cloud, int index);

  inline util::base::File* get_endedFrame(){return frame_ended;}

private:
  util::base::File* frame_onrun;
  util::base::File* frame_ended;
};
