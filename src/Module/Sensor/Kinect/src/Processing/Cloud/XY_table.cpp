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

  //Create cloud image
  k4a::image table_xy = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM, sensor->depth.cloud.width, sensor->depth.cloud.height, sensor->depth.cloud.width * sizeof(int16_t) * 3);


  std::vector<uint8_t> truc;
for(int i=0; i<sensor->depth.cloud.size; i++){
  truc.push_back(1);
}

  k4a::image machin = k4a::image::create_from_buffer(
    K4A_IMAGE_FORMAT_DEPTH16,
    sensor->depth.cloud.width,
    sensor->depth.cloud.height,
    sensor->depth.cloud.width * static_cast<int>(sizeof(uint16_t)),
    truc.data(),
    sensor->depth.cloud.size,
    nullptr,
    nullptr);


k4a_calibration_type_t calibration_type = sensor->depth.cloud.calibration_type;



  //Transform depth into cloud
  sensor->device.transformation.depth_image_to_point_cloud(machin, calibration_type, &table_xy);
  int size = table_xy.get_size() / (3 * sizeof(int16_t));
  uint8_t* buffer = table_xy.get_buffer();

  std::vector<uint16_t> bidule = sensor->device.table_xy;


utl::casting::uint8_to_vec_uint16(buffer, size, sensor->device.table_xy);

if(bidule.size() == 0) return;


int cpt = 0;
for(int i=0; i<size; i++){


  float arf = sensor->device.table_xy[i] - bidule[i];
  if(arf != 0) {
    say(arf);
cpt ++;
  }
}

//say(cpt);
  //---------------------------
}


}
