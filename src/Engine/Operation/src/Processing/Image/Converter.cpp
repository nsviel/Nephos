#include "Converter.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>



namespace ope::image{

//Constructor / Destructor
Converter::Converter(){
  //---------------------------

  this->utl_attribut = new utl::base::Attribut();

  //---------------------------
}
Converter::~Converter(){}

//Main function
void Converter::convert_normal_to_image(utl::base::Data* data, utl::media::Image* image){
  if(data == nullptr) return;
  //---------------------------

  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  if(Nxyz.size() == 0) return;

  std::vector<uint8_t> output = std::vector<uint8_t>(Nxyz.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<Nxyz.size(); i++){
    glm::vec3 normal = Nxyz[i];

    size_t j = i * 4;
    if(normal != glm::vec3(0, 0, 0)){
      output[j]     = (1 + normal.x) / 2 * 255.0f;
      output[j + 1] = (1 + normal.y) / 2 * 255.0f;
      output[j + 2] = (1 + normal.z) / 2 * 255.0f;
      output[j + 3] = 255.0f;
    }else{
      output[j]     = 0.0f;
      output[j + 1] = 0.0f;
      output[j + 2] = 0.0f;
      output[j + 3] = 255.0f;
    }
  }

  //Update image
  image->size = output.size();
  image->width = data->width;
  image->height = data->height;
  image->data = output;
  image->name = "Normal";

  //---------------------------
}
void Converter::convert_intensity_to_image(utl::base::Data* data, utl::media::Image* image){
  if(data == nullptr) return;
  //---------------------------

  std::vector<float>& vec_I = utl_attribut->get_field_data(data, "I");
  std::vector<uint8_t> output = std::vector<uint8_t>(vec_I.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<vec_I.size(); i++){
    float intensity = vec_I[i];

    size_t j = i * 4;
    output[j]     = intensity * 255.0f;
    output[j + 1] = intensity * 255.0f;
    output[j + 2] = intensity * 255.0f;
    output[j + 3] = 255.0f;
  }

  //Update image
  image->size = output.size();
  image->width = data->width;
  image->height = data->height;
  image->data = output;

  //---------------------------
}
void Converter::convert_color_to_image(utl::base::Data* data, utl::media::Image* image){
  if(data == nullptr) return;
  //---------------------------

  std::vector<uint8_t> output = std::vector<uint8_t>(data->rgb.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<data->rgb.size(); i++){
    glm::vec3& rgb = data->rgb[i];

    size_t j = i * 4;
    output[j]     = rgb.x * 255.0f;
    output[j + 1] = rgb.y * 255.0f;
    output[j + 2] = rgb.z * 255.0f;
    output[j + 3] = 255.0f;
  }

  //Update image
  image->size = output.size();
  image->width = data->width;
  image->height = data->height;
  image->data = output;

  //---------------------------
}

}
