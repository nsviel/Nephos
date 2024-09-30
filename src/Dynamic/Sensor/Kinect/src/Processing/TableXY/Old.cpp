/*#include "Table_xy.h"

#include <Kinect/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Table_xy::Table_xy(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Table_xy::~Table_xy(){}

//Main function
void Table_xy::thread_function(){
  if(!entity) return;
  //if(k4n_struct->transformation.mapping.size() != 0) return;
  //---------------------------

  auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
  if(auto k4n_sensor = std::dynamic_pointer_cast<k4n::base::Sensor>(sensor)){
    this->table_color_to_depth(*k4n_sensor);
    //this->convert_table_to_glm(k4n_sensor);
  }

  //---------------------------
}

//Subfunction
void Table_xy::build_texture(k4n::base::Sensor& sensor, k4a_calibration_type_t calibration_type){
  //---------------------------

  //Get calibration
  const k4a_calibration_camera_t& camera_calibration = calibration_type == K4A_CALIBRATION_TYPE_COLOR ?
    sensor.device.calibration.color_camera_calibration :
    sensor.device.calibration.depth_camera_calibration;

  int width = camera_calibration.resolution_width;
  int height = camera_calibration.resolution_height;

  //Create etxture
  k4a::image table_xy = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, width, height, width * static_cast<int>(sizeof(k4a_float2_t)));
  k4a_float2_t *data = reinterpret_cast<k4a_float2_t *>(table_xy.get_buffer());
  k4a_float2_t point_xy;
  k4a_float3_t point_xyz;

  //Fill texture
  for(int y=0, idx=0; y<height; y++){
    point_xy.xy.y = static_cast<float>(y);

    for(int x=0; x<width; x++, idx++){
      point_xy.xy.x = static_cast<float>(x);

      if(sensor.device.calibration.convert_2d_to_3d(point_xy, 1.f, calibration_type, calibration_type, &point_xyz)){
        data[idx].xy.x = point_xyz.xyz.x;
        data[idx].xy.y = point_xyz.xyz.y;
      }
      else{
        // The pixel is invalid
        data[idx].xy.x = 0.0f;
        data[idx].xy.y = 0.0f;
      }
    }
  }

  //---------------------------
}








void Table_xy::table_color_to_depth(k4n::base::Sensor& sensor){
  if(!sensor.depth.data.k4a_image) return;
  //---------------------------
say("table xy start");
  map_xy.clear();

  // Iterate through each pixel coordinate in the color image
  for(int y=0; y<sensor.color.image->height; y++){
    for(int x=0; x<sensor.color.image->width; x++){
      // Convert color coordinate to depth coordinate
      k4a_float2_t source_point2d = { static_cast<float>(x), static_cast<float>(y) };
      k4a_float2_t target_point2d;
      bool ok = sensor.device.calibration.convert_color_2d_to_depth_2d(source_point2d, sensor.depth.data.k4a_image, &target_point2d);
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
void Table_xy::apply_map(k4n::base::Sensor& sensor, int i){
  //---------------------------

  k4n::transformation::cmap& map_xy = k4n_struct->transformation.mapping;
  if(map_xy.size() != 0){
    int x = i % sensor.depth.data.width;
    int y = i / sensor.depth.data.width;

    float r, g, b;
    auto it = map_xy.find(glm::ivec2(x, y));
    if(it != map_xy.end()){
      glm::ivec2 coord_color = it->second;

      int idx = coord_color.y * sensor.color.image->width + coord_color.x;
      idx = idx * 4;

      r = static_cast<float>(sensor.color.image->data[idx + 2]) / 255.0f;
      g = static_cast<float>(sensor.color.image->data[idx + 1]) / 255.0f;
      b = static_cast<float>(sensor.color.image->data[idx + 0]) / 255.0f;
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

}*/
