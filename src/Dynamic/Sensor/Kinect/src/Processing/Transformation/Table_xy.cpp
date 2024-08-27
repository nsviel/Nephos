#include "Table_xy.h"

#include <Kinect/Namespace.h>

/*
unusefull class
was made for testing
bad results
*/


namespace k4n::processing::image{

//Constructor / Destructor
Table_xy::Table_xy(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Table_xy::~Table_xy(){}

//Main function
void Table_xy::thread_function(){
  if(sensor == nullptr) return;
  //if(k4n_struct->transformation.mapping.size() != 0) return;
  //---------------------------

  if (auto k4n_sensor = std::dynamic_pointer_cast<k4n::base::Sensor>(sensor)) {
    this->table_color_to_depth(k4n_sensor);
    //this->convert_table_to_glm(k4n_sensor);
  }

  //---------------------------
}

//Subfunction
void Table_xy::table_color_to_depth(std::shared_ptr<k4n::base::Sensor> sensor){
  if(!sensor->depth.data.k4a_image) return;
  //---------------------------
say("table xy start");
  map_xy.clear();

  // Iterate through each pixel coordinate in the color image
  for(int y=0; y<sensor->color.image.height; y++){
    for(int x=0; x<sensor->color.image.width; x++){
      // Convert color coordinate to depth coordinate
      k4a_float2_t source_point2d = { static_cast<float>(x), static_cast<float>(y) };
      k4a_float2_t target_point2d;
      bool ok = sensor->device.calibration.convert_color_2d_to_depth_2d(source_point2d, sensor->depth.data.k4a_image, &target_point2d);
      if(!ok) continue;

      //Save coordinate mapping
      int depthX = static_cast<int>(std::round(target_point2d.xy.x));
      int depthY = static_cast<int>(std::round(target_point2d.xy.y));
      map_xy[glm::ivec2(depthX, depthY)] = glm::ivec2(x, y);
    }
  }

  k4n_struct->transformation.mapping = map_xy;
say("table xy ok");
say(map_xy.size());
  //---------------------------
}
void Table_xy::apply_map(std::shared_ptr<k4n::base::Sensor> sensor, int i){
  //---------------------------

  k4n::transformation::cmap& map_xy = k4n_struct->transformation.mapping;
  if(map_xy.size() != 0){
    int x = i % sensor->depth.data.width;
    int y = i / sensor->depth.data.width;

    float r, g, b;
    auto it = map_xy.find(glm::ivec2(x, y));
    if(it != map_xy.end()){
      glm::ivec2 coord_color = it->second;

      int idx = coord_color.y * sensor->color.image.width + coord_color.x;
      idx = idx * 4;

      r = static_cast<float>(sensor->color.image.data[idx + 2]) / 255.0f;
      g = static_cast<float>(sensor->color.image.data[idx + 1]) / 255.0f;
      b = static_cast<float>(sensor->color.image.data[idx + 0]) / 255.0f;
    }else{
      r = 0;
      g = 0;
      b = 0;
    }

    //Store
    //buffer_data.rgb[i] = glm::vec3(r, g, b);
    //buffer_data.rgba[i] = glm::vec4(r, g, b, 1);
  }

  //---------------------------
}

}
