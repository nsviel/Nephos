#pragma once

#include <Utility/Specific/common.h>


namespace velodyne{

class Frame
{
public:
  //Constructor / Destructor
  Frame();
  ~Frame();

public:
  //Main functions
  bool build_frame(utl::media::File* data);
  void reset_frame();

  //Subfunctions
  void add_data_to_frame(utl::media::File* data);
  void end_data_to_frame(utl::media::File* data, int index);

  inline utl::media::File* get_endedFrame(){return frame_ended;}

private:
  utl::media::File* frame_onrun;
  utl::media::File* frame_ended;
};

}
