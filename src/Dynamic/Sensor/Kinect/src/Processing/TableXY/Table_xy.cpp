#include "Table_xy.h"

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
void Table_xy::build_table_xy(k4n::base::Sensor& sensor){
  //---------------------------

  this->build_texture(sensor, K4A_CALIBRATION_TYPE_COLOR);

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

}
