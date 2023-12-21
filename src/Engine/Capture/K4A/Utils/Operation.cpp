#include "Operation.h"


namespace eng::kinect{

//Constructor / Destructor
Operation::Operation(){
  //---------------------------


  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::make_colorization(eng::kinect::structure::Cloud* cloud, vector<vec4>& vec_rgba){
  //---------------------------

  //Colored unicolor
  if(cloud->color_mode == 1){
    vec_rgba = vector<vec4> (cloud->nb_point, cloud->object->unicolor);
  }
  //White unicolor
  else if(cloud->color_mode == 2){
    vec4 white = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec_rgba = vector<vec4> (cloud->nb_point, white);
  }
  //Heatmap
  else if(cloud->color_mode == 3){

  }

  //---------------------------
}

}
