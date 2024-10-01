#include "Table_xy.h"

#include <Kinect/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Table_xy::Table_xy(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Table_xy::~Table_xy(){}

//Main function
void Table_xy::build_table_xy(k4n::base::Sensor& sensor){
  //---------------------------

  //this->build_color_texture(sensor);
  this->build_depth_texture(sensor);

  //---------------------------
}

//Subfunction
void Table_xy::build_color_texture(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::media::Image> image = sensor.color.table_xy;
  if(image->size != 0) return;
  //---------------------------

  //Texture
  this->build_texture(sensor, *image, K4A_CALIBRATION_TYPE_COLOR);

  //Image
  image->display = false;
  image->size = image->data.size();
  image->format = "RG32";
  dat_image->add_image(sensor, image);

  //---------------------------
}
void Table_xy::build_depth_texture(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::media::Image> image = sensor.depth.table_xy;
  if(image->size != 0) return;
  //---------------------------

  //Texture
  this->build_texture(sensor, *image, K4A_CALIBRATION_TYPE_DEPTH);

  //Image
  image->display = false;
  image->size = image->data.size();
  image->format = "RG32";
  dat_image->add_image(sensor, image);

  //---------------------------
}
void Table_xy::build_texture(k4n::base::Sensor& sensor, utl::media::Image& image, k4a_calibration_type_t calibration_type){
  //---------------------------

  //Get calibration
  const k4a_calibration_camera_t& camera_calibration =
    calibration_type == K4A_CALIBRATION_TYPE_COLOR ?
    sensor.device.calibration.color_camera_calibration :
    sensor.device.calibration.depth_camera_calibration;

  //Get variables
  image.width = camera_calibration.resolution_width;
  image.height = camera_calibration.resolution_height;
  image.data = std::vector<uint8_t>(image.width * image.height * sizeof(float) * 2);
  float* data_ptr = reinterpret_cast<float*>(image.data.data());
  k4a_float2_t point_xy;
  k4a_float3_t point_xyz;

  //Fill texture
  for(int y=0; y<image.height; y++){
    point_xy.xy.y = static_cast<float>(y);

    for(int x=0; x<image.width; x++){
      point_xy.xy.x = static_cast<float>(x);
      int idx = (y * image.width + x) * 2;

      if(sensor.device.calibration.convert_2d_to_3d(point_xy, 1.f, calibration_type, calibration_type, &point_xyz)){
        image.data[idx] = point_xyz.xyz.x;
        image.data[idx + 1] = point_xyz.xyz.y;

        if((idx == 0)) say(point_xyz.xyz.x);
      }
      else{
        // The pixel is invalid
        image.data[idx] = 0.0f;
        image.data[idx + 1] = 0.0f;

      }
    }
  }

  float* floatData = reinterpret_cast<float*>(image.data.data());
  float value = floatData[0];
  say(value);

  //---------------------------
}

}
