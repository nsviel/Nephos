#include "Data.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>
#include <Processing/Namespace.h>


namespace k4n::infrared{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();
  dyn::prc::Node* node_processing = node_k4n->get_node_processing();

  this->dat_image = node_image->get_dat_image();
  this->dat_depth = node_image->get_dat_depth();
  this->dyn_struct = node_processing->get_dyn_struct();
  this->k4n_format = new k4n::infrared::Format(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::extract_data(k4n::base::Sensor& sensor){
  //---------------------------

  this->retrieve_data(sensor);
  this->retrieve_raw_image(sensor);
  this->retrieve_colored_image(sensor);

  //---------------------------
}

//Subfunction
void Data::retrieve_data(k4n::base::Sensor& sensor){
  //---------------------------

  //Get k4a image
  k4a::image ir = sensor.device.capture->get_ir_image();
  if(!ir.is_valid()) return;

  //Data
  sensor.infra.data.image = ir;
  sensor.infra.data.width = ir.get_width_pixels();
  sensor.infra.data.height = ir.get_height_pixels();
  sensor.infra.data.buffer = ir.get_buffer();
  sensor.infra.data.size = ir.get_size();
  sensor.infra.data.format = k4n_format->retrieve_format(ir.get_format());
  sensor.infra.data.timestamp = static_cast<float>(ir.get_device_timestamp().count() / 1000000.0f);
  type::uint8_to_vec_uint16(sensor.infra.data.buffer, sensor.infra.data.size, sensor.info.buffer_ir);

  //---------------------------
}
void Data::retrieve_raw_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Depth> image = sensor.infra.texture.depth;
  //---------------------------

  //Image
  k4n_format->convert_buffer_into_uint16(sensor);
  image->size = image->data.size();
  image->width = sensor.infra.data.width;
  image->height = sensor.infra.data.height;
  image->format = "R16_UINT";
  dat_depth->add_depth(sensor, image);

  //---------------------------
}
void Data::retrieve_colored_image(k4n::base::Sensor& sensor){
  std::shared_ptr<utl::base::Image> image = sensor.infra.texture.image;
  //---------------------------

  //Image
  k4n_format->convert_buffer_into_color(sensor);
  image->size = image->data.size();
  image->width = sensor.infra.data.width;
  image->height = sensor.infra.data.height;
  image->format = "RGBA8";
  image->timestamp = sensor.infra.data.timestamp;
  dat_image->add_image(sensor, image);

  //---------------------------
}

}
