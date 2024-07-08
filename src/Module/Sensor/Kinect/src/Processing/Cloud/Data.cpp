#include "Data.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::processing::cloud{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_xytable = new k4n::processing::cloud::XY_table(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::extract_data(k4n::base::Sensor* sensor){
  if(check_condition(sensor) == false) return;
  //---------------------------

  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("kinect::cloud");

  tasker->loop();



  //init
  tasker->task_begin("init");
  this->extraction_init(sensor);
  tasker->task_end("init");

  //Extraction
  tasker->task_begin("extraction");
  this->extraction_data(sensor);
  tasker->task_end("extraction");

  //Transfer
  tasker->task_begin("transfer");
  this->extraction_transfer(sensor);
  tasker->task_end("transfer");

    k4n_xytable->retrieve_table_xy(sensor);

  //---------------------------
}

//Subfunction
bool Data::check_condition(k4n::base::Sensor* sensor){
  //---------------------------

  if(!sensor->depth.data.k4a_image.is_valid()) return false;
  if(!sensor->ir.data.k4a_image.is_valid()) return false;
  if(sensor->color.data.buffer == nullptr) return false;
  if(sensor->color.data.size != sensor->depth.data.size * 2) return false;

  //---------------------------
  return true;
}
void Data::extraction_init(k4n::base::Sensor* sensor){
  //---------------------------

  //Create cloud image
  k4a::image cloud_image = k4a::image::create(
    K4A_IMAGE_FORMAT_CUSTOM,
    sensor->depth.data.width,
    sensor->depth.data.height,
    sensor->depth.data.width * sizeof(int16_t) * 3
  );

  //Transform depth into cloud
  sensor->device.transformation.depth_image_to_point_cloud(sensor->depth.data.k4a_image, sensor->cloud.calibration_type, &cloud_image);
  sensor->cloud.buffer = cloud_image.get_buffer();
  sensor->cloud.size = cloud_image.get_size() / (3 * sizeof(int16_t));

  //Resize vectors
  buffer_data.xyz.resize(sensor->cloud.size);
  buffer_data.rgb.resize(sensor->cloud.size);
  buffer_data.Is.resize(sensor->cloud.size);
  buffer_data.R.resize(sensor->cloud.size);

  //---------------------------
}
void Data::extraction_data(k4n::base::Sensor* sensor){
  //---------------------------

  //Fille vector with data
  #pragma omp parallel for
  for(int i=0; i<sensor->cloud.size; i++){
    //this->retrieve_location(sensor, i);
    this->retrieve_color(sensor, i);
    this->retrieve_ir(sensor, i);
  }

  std::vector<glm::vec3> vec_xyz(sensor->cloud.size);
  for(int i=0; i<sensor->cloud.size; i++){
    //Real location
    const int16_t* buffer_depth = reinterpret_cast<int16_t*>(sensor->cloud.buffer);
    int idx = i * 3;
    float x = buffer_depth[idx + 0];
    float y = buffer_depth[idx + 1];
    float z = buffer_depth[idx + 2];
    float x_m = -x / 1000.0f;
    float y_m = -y / 1000.0f;
    float z_m = z / 1000.0f;
    glm::vec3 xyz = glm::vec3(z_m, x_m, y_m);
    buffer_data[i] = xyz;


  }
    buffer_data.xyz = vec_xyz;
    sensor->data.xyz = vec_xyz;

  //---------------------------
}
void Data::extraction_transfer(k4n::base::Sensor* sensor){
  utl::base::Data* data = &sensor->data;
  //---------------------------

  //Data
  data->xyz = buffer_data.xyz;
  data->rgb = buffer_data.rgb;
  data->Is = buffer_data.Is;
  data->R = buffer_data.R;

  //Info
  data->size = sensor->cloud.size;
  data->width = sensor->cloud.width;
  data->height = sensor->cloud.height;

  //---------------------------
}

//Data function
void Data::retrieve_location(k4n::base::Sensor* sensor, int i){
  const int16_t* buffer_depth = reinterpret_cast<int16_t*>(sensor->cloud.buffer);
  //---------------------------

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
  buffer_data.xyz[i] = xyz;
  buffer_data.R[i] = R;

  //---------------------------
}
void Data::retrieve_color(k4n::base::Sensor* sensor, int i){
  const uint8_t* buffer_color = sensor->color.data.buffer;
  //---------------------------

  //Raw values
  int idx = i * 4;
  float r = static_cast<float>(buffer_color[idx + 2]) / 255.0f;
  float g = static_cast<float>(buffer_color[idx + 1]) / 255.0f;
  float b = static_cast<float>(buffer_color[idx + 0]) / 255.0f;

  //Store
  buffer_data.rgb[i] = glm::vec3(r, g, b);

  //---------------------------
}
void Data::retrieve_ir(k4n::base::Sensor* sensor, int i){
  const int16_t* buffer_ir = reinterpret_cast<int16_t*>(sensor->ir.data.buffer);
  //---------------------------

  //Raw values
  float ir = buffer_ir[i];

  //Store
  buffer_data.Is[i] = ir;

  //---------------------------
}

}
