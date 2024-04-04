#pragma once

#include <Utility/Specific/Common.h>


namespace vld{

class Frame
{
public:
  //Constructor / Destructor
  Frame();
  ~Frame();

public:
  //Main functions
  bool build_frame(utl::file::Entity* data);
  void reset_frame();

  //Subfunctions
  void add_data_to_frame(utl::file::Entity* data);
  void end_data_to_frame(utl::file::Entity* data, int index);

  inline utl::file::Entity* get_endedFrame(){return frame_ended;}

private:
  utl::file::Entity* frame_onrun;
  utl::file::Entity* frame_ended;
};

}
