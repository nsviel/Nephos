#include "Operation.h"


namespace eng::kinect{

//Constructor / Destructor
Operation::Operation(){
  //---------------------------


  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::make_colorization(eng::kinect::structure::Cloud* cloud, std::vector<glm::vec4>& vec_rgba){
  //---------------------------

  vec_rgba.clear();
  for(int i=0; i<cloud->object->xyz.size(); i++){
    glm::vec4 color;

    //Colored unicolor
    if(cloud->color_mode == 1){

      color = cloud->object->unicolor;
    }
    //White unicolor
    else if(cloud->color_mode == 2){

      color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
    //Heatmap
    else if(cloud->color_mode == 3){

    }

    vec_rgba.push_back(color);
  }

  //---------------------------
}

}
