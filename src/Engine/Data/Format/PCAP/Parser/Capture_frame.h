#pragma once

#include <Utility/Base/Struct_file.h>
#include <Utility/UTL_function/fct_math.h>
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
  bool build_frame(data::File* cloud);
  void reset_frame();

  //Subfunctions
  void add_cloudsToFrame(data::File* cloud);
  void end_cloudsToFrame(data::File* cloud, int index);

  inline data::File* get_endedFrame(){return frame_ended;}

private:
  data::File* frame_onrun;
  data::File* frame_ended;
};
