#include "Converter.h"

#include <Operation/Namespace.h>


namespace ope::color{

//Constructor / Destructor
Converter::Converter(){
  //---------------------------


  //---------------------------
}
Converter::~Converter(){}

//Main function
void Converter::convert_normal_to_image(dat::base::Entity* entity){
  utl::base::Data* data = entity->get_data();
  //---------------------------

  vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<uint8_t> output = std::vector<uint8_t>(Nxyz.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<Nxyz.size(); i++){
    glm::vec3 normal = Nxyz[i];

    size_t j = i * 4;
    output[j] = normal.x * 255.0f;
    output[j + 1] = normal.y * 255.0f;
    output[j + 2] = normal.z * 255.0f;
    output[j + 3] = 255;
  }

  //sensor->normal.image.data = output;

  //---------------------------
}

}
