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
    }
    case 2:{//White unicolor
      vec4 white = vec4(1.0f, 1.0f, 1.0f, 1.0f);
      vec_rgba = vector<vec4> (cloud->nb_point, white);
    }
    case 3:{//Heatmap
      this->make_heatmap(cloud, vec_rgba);
    }
  }

  //---------------------------
}
void Operation::make_heatmap(eng::kinect::structure::Cloud* cloud, vector<vec4>& vec_rgba){
  //---------------------------

  switch(cloud->heatmap_mode){
    case 0:{//Intensity
      vec_rgba = ope_heatmap->heatmap_height(cloud->object);
    }
    case 1:{//Height
      vec_rgba = ope_heatmap->heatmap_height(cloud->object);
    }
  }

  //---------------------------
}

}
