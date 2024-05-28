#include "Converter.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>



namespace ope::image{

//Constructor / Destructor
Converter::Converter(){
  //---------------------------

  this->ope_image = new ope::image::Manager();

  //---------------------------
}
Converter::~Converter(){}

//Main function
void Converter::convert_normal_to_image(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  utl::base::Data* data = entity->get_data();
  vector<glm::vec3>& Nxyz = data->Nxyz;
  if(data->Nxyz.size() == 0) return;
  std::vector<uint8_t> output = std::vector<uint8_t>(Nxyz.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<Nxyz.size(); i++){
    glm::vec3 normal = Nxyz[i];

    size_t j = i * 4;
    output[j]     = normal.x * 255.0f;
    output[j + 1] = normal.x * 255.0f;
    output[j + 2] = normal.x * 255.0f;
    output[j + 3] = 255.0f;
  }

  //Update image
  utl::media::Image* image = ope_image->get_or_create_image(entity, utl::media::NORMAL);
  image->size = output.size();
  image->width = data->width;
  image->height = data->height;
  image->data = output;
  image->new_data = true;
  image->data = output;
  image->name = "Normal";

  //---------------------------
}

}
