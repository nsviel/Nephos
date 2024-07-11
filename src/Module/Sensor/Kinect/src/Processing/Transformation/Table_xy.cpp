#include "Table_xy.h"

#include <Kinect/Namespace.h>


namespace k4n::processing::image{

struct Vec2Hash {
  std::size_t operator()(const glm::ivec2& vec) const {
    // Combine hash of x and y using a simple hash function
    return std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1);
  }
};
struct Vec2Equal {
  bool operator()(const glm::ivec2& a, const glm::ivec2& b) const {
    return a.x == b.x && a.y == b.y;
  }
};

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
  //---------------------------

  if(k4n::base::Sensor* k4n_sensor = dynamic_cast<k4n::base::Sensor*>(sensor)){
    this->table_color_to_depth(k4n_sensor);
  }

  //---------------------------
}

//Subfunction
void Table_xy::table_color_to_depth(k4n::base::Sensor* sensor){
  if(!sensor->color.data.k4a_image || !sensor->depth.data.k4a_image) return;
  //---------------------------

  // Iterate through each pixel coordinate in the color image
  std::unordered_map<glm::ivec2, glm::ivec2, Vec2Hash, Vec2Equal> map_xy;
  for(int y=0; y<sensor->color.data.height; y++){
    for(int x=0; x<sensor->color.data.width; x++){
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

  //---------------------------
}
void Table_xy::convert_table_to_glm(k4n::base::Sensor* sensor){
  //---------------------------

  std::unordered_map<glm::ivec2, glm::ivec2, Vec2Hash, Vec2Equal> map_xy;

  std::vector<glm::ivec4>& table_xy = k4n_struct->transformation.table_xy;
  for(int y=0; y<sensor->color.data.height; y++){
    for(int x=0; x<sensor->color.data.width; x++){
      glm::ivec2 depth = glm::ivec2(x, y);
      glm::ivec2 color = map_xy[depth];
      glm::ivec4 coordinate = glm::ivec4(depth.x, depth.y, color.x, color.y);
      table_xy.push_back(coordinate);
    }
  }

  //---------------------------
}

}
