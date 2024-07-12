#include "Frame.h"

#include <Utility/Namespace.h>


namespace vld::processing{

//Constructor / Destructor
Frame::Frame(){
  //---------------------------

  this->frame_onrun = new utl::base::Data();
  this->frame_ended = new utl::base::Data();
  this->utl_attribut = new utl::base::Attribut();

  //---------------------------
}
Frame::~Frame(){}

//Main function
bool Frame::build_frame(utl::base::Data* data){
  bool frame_ended = false;
  //---------------------------

  //check if the new cloud begin by a revolution
  // frame_index -1: new frame
  // frame_index 0: frame end and restart at 0
  // frame_index i: frame end at point i
  if(data->A.size() != 0){
    //First case: no previous frame created
    int frame_index = -1;

    //Second case: the packet is the first of a frame, but the previousframe should have 10k pts
    if(frame_onrun->A.size() > 10000){
      if(data->A[0] + 350 < frame_onrun->A[frame_onrun->A.size()-1] ){
        frame_index = 0;
      }
    }
    //Third case: we search if or not the end of the frame in inside the packet
    //This happen rarely
    else{
      for(int i=0; i<data->A.size() - 1; i++){
        if( data->A[i+1] < data->A[i] ){
          frame_index = i;
          say("thats happen !");
          break;
        }
      }
    }

    //say(data->A[data->A.size()-1]);
    //Then: first case or no index found
    if(frame_index == -1){
      this->add_data_to_frame(data);
      frame_ended = false;
    }
    //Then: second and third cases where an end index was found
    else{
      this->end_data_to_frame(data, frame_index);
      frame_ended = true;
    }
  }

  //---------------------------
  delete data;
  return frame_ended;
}
void Frame::reset_frame(){
  //---------------------------

  delete frame_onrun;
  delete frame_ended;

  this->frame_onrun = new utl::base::Data();
  this->frame_ended = new utl::base::Data();

  //---------------------------
}

//Subfunctions
void Frame::add_data_to_frame(utl::base::Data* data){
  //---------------------------

  std::vector<float>& vec_R = utl_attribut->get_attribut_data(data, "R");

  for(int i=0; i<data->xyz.size(); i++){
    frame_onrun->xyz.push_back(data->xyz[i]);
    frame_onrun->R.push_back(vec_R[i]);
    frame_onrun->Is.push_back(data->Is[i]/255);
    frame_onrun->A.push_back(data->A[i]);
    frame_onrun->ts.push_back(data->ts[i]);
  }

  //---------------------------
}
void Frame::end_data_to_frame(utl::base::Data* data, int index){
  //---------------------------

  std::vector<float>& vec_R = utl_attribut->get_attribut_data(data, "R");
  
  for(int i=0; i<index; i++){
    frame_onrun->xyz.push_back(data->xyz[i]);
    frame_onrun->R.push_back(vec_R[i]);
    frame_onrun->Is.push_back(data->Is[i]/255);
    frame_onrun->A.push_back(data->A[i]);
    frame_onrun->ts.push_back(data->ts[i]);
  }

  *frame_ended = *frame_onrun;
  delete frame_onrun;
  frame_onrun = new utl::base::Data();

  for(int i=index; i<data->xyz.size(); i++){
    frame_onrun->xyz.push_back(data->xyz[i]);
    frame_onrun->R.push_back(vec_R[i]);
    frame_onrun->Is.push_back(data->Is[i]/255);
    frame_onrun->A.push_back(data->A[i]);
    frame_onrun->ts.push_back(data->ts[i]);
  }

  //---------------------------
}

}
