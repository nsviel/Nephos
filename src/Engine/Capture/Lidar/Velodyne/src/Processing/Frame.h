#pragma once

#include <Utility/Specific/Common.h>


namespace vld::processing{

class Frame
{
public:
  //Constructor / Destructor
  Frame();
  ~Frame();

public:
  //Main functions
  bool build_frame(utl::file::Data* data);
  void reset_frame();

  //Subfunctions
  void add_data_to_frame(utl::file::Data* data);
  void end_data_to_frame(utl::file::Data* data, int index);

  inline utl::file::Data* get_endedFrame(){return frame_ended;}

private:
  utl::file::Data* frame_onrun;
  utl::file::Data* frame_ended;
};

}
