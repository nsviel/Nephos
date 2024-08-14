#pragma once

namespace utl::base{class Data;}
namespace utl::base{class Attribut;}


namespace vld::processing{

class Frame
{
public:
  //Constructor / Destructor
  Frame();
  ~Frame();

public:
  //Main function
  bool build_frame(utl::base::Data* data);
  void reset_frame();

  //Subfunctions
  void add_data_to_frame(utl::base::Data* data);
  void end_data_to_frame(utl::base::Data* data, int index);

  inline utl::base::Data* get_endedFrame(){return frame_ended;}

private:
  utl::base::Data* frame_onrun;
  utl::base::Data* frame_ended;
  utl::base::Attribut* utl_attribut;
};

}