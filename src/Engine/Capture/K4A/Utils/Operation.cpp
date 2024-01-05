#include "Operation.h"


namespace eng::kinect{

//Constructor / Destructor
Operation::Operation(){
  //---------------------------

  this->ope_heatmap = new eng::ope::Heatmap();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::make_colorization(eng::kinect::structure::Cloud* cloud, vector<vec4>& vec_rgba){
  //---------------------------

  switch(cloud->color_mode){
    case 1:{//Colored unicolor
      vec_rgba = vector<vec4> (cloud->nb_point, cloud->object->unicolor);
      break;
    }
    case 2:{//White unicolor
      this->colorization_intensity(cloud, vec_rgba);
      break;
    }
    case 3:{//Heatmap
      this->colorization_heatmap(cloud, vec_rgba);
      break;
    }
  }

  //---------------------------
}
void Operation::colorization_intensity(eng::kinect::structure::Cloud* cloud, vector<vec4>& vec_rgba){
  //---------------------------

  vec_rgba.clear();
  vec_rgba.reserve(cloud->nb_point);
  for(int i=0; i<cloud->nb_point; i++){
    float Is = cloud->object->Is[i] / cloud->intensity_division;
    vec_rgba.push_back(vec4(Is, Is, Is, 1));
  }

  //---------------------------
}
void Operation::colorization_heatmap(eng::kinect::structure::Cloud* cloud, vector<vec4>& vec_rgba){
  //---------------------------

  switch(cloud->heatmap_mode){
    case 0:{//Intensity
      vec_rgba = ope_heatmap->heatmap_intensity(cloud->object, cloud->intensity_division);
      break;
    }
    case 1:{//Height
      vec_rgba = ope_heatmap->heatmap_height(cloud->object, cloud->range_height);
      break;
    }
  }

  //---------------------------
}

}
