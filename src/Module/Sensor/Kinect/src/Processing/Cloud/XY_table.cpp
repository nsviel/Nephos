#include "XY_table.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::processing::cloud{

//Constructor / Destructor
XY_table::XY_table(k4n::Node* node_k4n){
  //---------------------------

  //---------------------------
}
XY_table::~XY_table(){}

//Main function
void XY_table::retrieve_table_xy(k4n::structure::Sensor* sensor){
  //---------------------------

  //Create full 1 value image
  std::vector<uint8_t> vec_2;
  for(size_t i=0; i<sensor->depth.data.size; i++){
    vec_2.push_back(i % 2); // Alternating 0 and 1
  }
  k4a::image image_full_1 = k4a::image::create_from_buffer(
    K4A_IMAGE_FORMAT_DEPTH16,
    sensor->depth.data.width,
    sensor->depth.data.height,
    sensor->depth.data.width * sizeof(uint16_t),
    vec_2.data(),
    vec_2.size(),
    nullptr,
    nullptr
  );

  //Transform depth into cloud
  k4a::image table_xy = k4a::image::create(
    K4A_IMAGE_FORMAT_CUSTOM,
    sensor->depth.data.width,
    sensor->depth.data.height,
    sensor->depth.data.width * sizeof(int16_t) * 3
  );
  //sensor->device.transformation.depth_image_to_point_cloud(image_full_1, K4A_CALIBRATION_TYPE_DEPTH, &table_xy);

  /*
  //Convert buffer to vector of uint16_t
  int size = table_xy.get_size() / (3 * sizeof(int16_t));

  //Post-processing
  uint8_t* ran_buffer = table_xy.get_buffer();
  const int16_t* buffer_depth = reinterpret_cast<int16_t*>(ran_buffer);
  for(int i=0; i<size; i++){
    //Raw values
    int idx = i * 3;
    float x = buffer_depth[idx + 0];
    float y = buffer_depth[idx + 1];
    float z = buffer_depth[idx + 2];

    //Compute final values
    glm::vec3 xyz = glm::vec3(x, y, z);

    say("----");
    say(xyz);
  }*/

  k4a::image color_to_depth = sensor->device.transformation.color_image_to_depth_camera(image_full_1, sensor->color.data.k4a_image);
  if(!color_to_depth.is_valid()) return;

  say(sensor->color.data.k4a_image.get_size());
  say(color_to_depth.get_size());

  //---------------------------
}



}
