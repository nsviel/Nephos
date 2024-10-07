#include "Data.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::image{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->dat_image = node_image->get_dat_image();
  this->dat_depth = node_image->get_dat_depth();
  this->k4n_format = new k4n::depth::Format(node_k4n);
  this->k4n_texture = new k4n::depth::Texture(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->retrieve_data(sensor);
  k4n_texture->retrieve_raw_image(sensor);
  k4n_texture->retrieve_colored_image(sensor);

  //---------------------------
}

//Subfunction
void Data::retrieve_data(k4n::base::Sensor& sensor){
  //---------------------------

  //Get k4a image
  k4a::image depth = sensor.device.capture->get_depth_image();
  if(!depth.is_valid()) return;

  //Data
  sensor.depth.data.image = depth;
  sensor.depth.data.width = depth.get_width_pixels();
  sensor.depth.data.height = depth.get_height_pixels();
  sensor.depth.data.buffer = depth.get_buffer();
  sensor.depth.data.size = depth.get_size();
  sensor.depth.data.format = k4n_format->retrieve_format(depth.get_format());
  sensor.depth.data.temperature = sensor.device.capture->get_temperature_c();
  sensor.depth.data.timestamp = static_cast<float>(depth.get_device_timestamp().count() / 1000000.0f);
  type::uint8_to_vec_uint16(sensor.depth.data.buffer, sensor.depth.data.size, sensor.info.buffer_depth);

  //---------------------------
}
void Data::depth_to_cloud(k4n::base::Sensor& sensor){
  //---------------------------

  //Create cloud image
  sensor.depth.cloud.image = k4a::image::create(
    K4A_IMAGE_FORMAT_CUSTOM,
    sensor.depth.data.width,
    sensor.depth.data.height,
    sensor.depth.data.width * sizeof(int16_t) * 3
  );

  //Transform depth into cloud
  sensor.device.transformation.depth_image_to_point_cloud(sensor.depth.data.image, sensor.device.calibration_type, &sensor.depth.cloud.image);
  sensor.depth.cloud.buffer = sensor.depth.cloud.image.get_buffer();
  sensor.depth.cloud.size = sensor.depth.cloud.image.get_size() / (3 * sizeof(int16_t));

  //Resize vectors
  sensor.depth.data.xyz.resize(sensor.depth.cloud.size);
  sensor.depth.data.R.resize(sensor.depth.cloud.size);
  sensor.color.data.rgb.resize(sensor.depth.cloud.size);
  sensor.color.data.rgba.resize(sensor.depth.cloud.size);
  sensor.infra.data.Is.resize(sensor.depth.cloud.size);

  //---------------------------
}
void Data::extract_cloud_xyz(k4n::base::Sensor& sensor){
  //---------------------------

  //Fille vector with data
  #pragma omp parallel for
  for(int i=0; i<sensor.depth.cloud.size; i++){
    const int16_t* buffer_depth = reinterpret_cast<int16_t*>(sensor.depth.cloud.buffer);

    //Raw values
    int idx = i * 3;
    float x = buffer_depth[idx + 0];
    float y = buffer_depth[idx + 1];
    float z = buffer_depth[idx + 2];

    //Convert coordinate in meter and X axis oriented.
    float x_m = -x / 1000.0f;
    float y_m = -y / 1000.0f;
    float z_m = z / 1000.0f;

    //Compute final values
    glm::vec3 xyz = glm::vec3(z_m, x_m, y_m);
    float R = math::distance_from_origin(xyz);

    //Store
    sensor.depth.data.xyz[i] = xyz;
    sensor.depth.data.R[i] = R;
  }

  //---------------------------
}

}
