#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Math/Math.h>
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
  bool build_frame(utl::media::File* cloud);
  void reset_frame();

  //Subfunctions
  void add_cloudsToFrame(utl::media::File* cloud);
  void end_cloudsToFrame(utl::media::File* cloud, int index);

  inline utl::media::File* get_endedFrame(){return frame_ended;}

private:
  utl::media::File* frame_onrun;
  utl::media::File* frame_ended;
};
