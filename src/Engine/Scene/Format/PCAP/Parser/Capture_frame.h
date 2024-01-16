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
  bool build_frame(utl::base::File* cloud);
  void reset_frame();

  //Subfunctions
  void add_cloudsToFrame(utl::base::File* cloud);
  void end_cloudsToFrame(utl::base::File* cloud, int index);

  inline utl::base::File* get_endedFrame(){return frame_ended;}

private:
  utl::base::File* frame_onrun;
  utl::base::File* frame_ended;
};
