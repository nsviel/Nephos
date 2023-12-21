#include "Operation.h"


namespace eng::kinect{

//Constructor / Destructor
Operation::Operation(){
  //---------------------------


  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::make_colorization(vector<vec4>& vec_rgba, int size, int mode, vec4 unicolor){
  //---------------------------

  //Colored unicolor
  if(mode == 1){
    vec_rgba = vector<vec4> (size, unicolor);
  }
  //White unicolor
  if(mode == 2){
    vec4 white = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec_rgba = vector<vec4> (size, white);
  }
  //Heatmap
  else if(mode == 3){

  }
  
  //---------------------------
}

}
