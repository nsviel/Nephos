#include "Table_xy.h"

#include <Kinect/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Table_xy::Table_xy(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_storage = node_image->get_dat_storage();
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
  std::shared_ptr<utl::base::Storage> storage = sensor.color.texture.table_xy;
  if(storage->size != 0) return;
  //---------------------------

  //Texture
  this->build_texture(sensor, *storage, K4A_CALIBRATION_TYPE_COLOR);

  //Image
  storage->size = storage->data.size();
  storage->format = "RG32";
  dat_storage->add_storage(sensor, storage);

  //---------------------------
}
void Table_xy::build_depth_texture(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Storage> storage = sensor.depth.texture.table_xy;
  if(storage->size != 0) return;
  //---------------------------

  //Texture
  this->build_texture(sensor, *storage, K4A_CALIBRATION_TYPE_DEPTH);

  //Image
  storage->size = storage->data.size();
  storage->format = "RG32";
  dat_storage->add_storage(sensor, storage);

  //---------------------------
}
void Table_xy::build_texture(k4n::base::Sensor& sensor, utl::base::Storage& storage, k4a_calibration_type_t calibration_type){
  //---------------------------

  //Get calibration
  const k4a_calibration_camera_t& camera_calibration =
    calibration_type == K4A_CALIBRATION_TYPE_COLOR ?
    sensor.device.calibration.color_camera_calibration :
    sensor.device.calibration.depth_camera_calibration;

  //Get variables
  storage.width = camera_calibration.resolution_width;
  storage.height = camera_calibration.resolution_height;
  storage.data = std::vector<float>(storage.width * storage.height * 2);
  k4a_float2_t point_xy;
  k4a_float3_t point_xyz;

  //Fill texture
  for(int y=0; y<storage.height; y++){
    point_xy.xy.y = static_cast<float>(y);

    for(int x=0; x<storage.width; x++){
      point_xy.xy.x = static_cast<float>(x);
      int idx = (y * storage.width + x) * 2;

      if(sensor.device.calibration.convert_2d_to_3d(point_xy, 1.f, calibration_type, calibration_type, &point_xyz)){
        storage.data[idx] = point_xyz.xyz.x;
        storage.data[idx + 1] = point_xyz.xyz.y;
      }
      else{
        // The pixel is invalid
        storage.data[idx] = 0.0f;
        storage.data[idx + 1] = 0.0f;
      }
    }
  }

  //---------------------------
}

}
