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
void XY_table::find_table_xy(std::shared_ptr<k4n::base::Sensor> sensor){
  if(sensor->cloud.table_xy.size() != 0) return;
  //---------------------------

  sensor->cloud.table_xy.resize(sensor->depth.data.size);
  for(int i=0; i<sensor->depth.data.height; i++){
    for(int j=0; j<sensor->depth.data.width; j++){
      //Gat table value
      k4a_float2_t source_xy = { static_cast<float>(i), static_cast<float>(j) };
      k4a_float3_t target_xyz;
      sensor->device.calibration.convert_2d_to_3d(source_xy, 1, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &target_xyz);

      //Store value
      int idx = i * sensor->depth.data.width + j;
      sensor->cloud.table_xy[idx] = glm::vec2(target_xyz.xyz.x, target_xyz.xyz.y);
    }
  }

  //---------------------------
}
void XY_table::find_value(std::shared_ptr<k4n::base::Sensor> sensor, int i){
  //---------------------------

  std::vector<glm::vec2>& table_xy = sensor->cloud.table_xy;
  const int16_t* buffer_raw = reinterpret_cast<int16_t*>(sensor->depth.data.buffer);
  float depth = buffer_raw[i];
  float x = table_xy[i].x*depth;
  float y = table_xy[i].y*depth;
  float z = depth;
  float x_m = -x / 1000.0f;
  float y_m = -y / 1000.0f;
  float z_m = z / 1000.0f;
  glm::vec3 xyz = glm::vec3(z_m, y_m, x_m);

  //---------------------------
}


}
