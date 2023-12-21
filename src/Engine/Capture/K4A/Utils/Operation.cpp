#include "Operation.h"


namespace eng::kinect{

//Constructor / Destructor
Operation::Operation(){
  //---------------------------


  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::make_colorization(vector<vec4>& vec_rgba, int size, int mode){
  //---------------------------
  tic();
  vec4 defaultValue = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  vec_rgba = vector<vec4> (size, defaultValue);

/*
  vec_rgba.clear();
  vec_rgba.reserve(size);
  for(int i=0; i<size; i++){
    vec4 color;

    //Colored unicolor
    if(mode == 1){
//
  //    color = cloud->object->unicolor;
    }
    //White unicolor
    else if(mode == 2){

      color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
    //Heatmap
    else if(mode == 3){

    }

    vec_rgba.push_back(color);
  }*/
  say(size);
  say(vec_rgba.size());
toc_us("hey");
  //---------------------------
}

}
