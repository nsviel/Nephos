#pragma once

#include "../../../Scene/Base/struct_data_file.h"
#include "../../../common.h"


namespace eng::vlp16{

class Frame
{
public:
  //Constructor / Destructor
  Frame();
  ~Frame();

public:
  //Main functions
  bool build_frame(Data_file* cloud);
  void reset_frame();

  //Subfunctions
  void add_cloudsToFrame(Data_file* cloud);
  void end_cloudsToFrame(Data_file* cloud, int index);

  inline Data_file* get_endedFrame(){return frame_ended;}

private:
  Data_file* frame_onrun;
  Data_file* frame_ended;
};

}
