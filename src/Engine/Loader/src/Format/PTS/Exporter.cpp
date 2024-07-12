#include "Exporter.h"

#include <Data/Namespace.h>
#include <Utility/Function/File/File.h>


namespace fmt::pts{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->utl_attribut = new utl::base::Attribut();
  
  this->format = ".pts";
  this->vec_encoding.push_back(ldr::io::ASCII);

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::export_ascii(utl::base::Data* data, glm::mat4 mat, std::string path){
  //---------------------------

  //Create file
  if(path.substr(path.find_last_of(".") + 1) != "pts") path.append(".pts");
  std::ofstream file;
  file.open(path);
  if(!file){
    std::cout<<"Error in creating file !";
    return;
  }

  //Data : xyz (R) (rgb) (nxnynz)
  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
  std::vector<glm::vec3>& N = data->Nxyz;
  std::vector<float>& vec_I = utl_attribut->get_attribut_data(data, "I");

  //Write in the file
  int precision = 6;
  file << xyz.size() << std::endl;
  for(int i=0; i<xyz.size(); i++){
    //Line start
    file << std::fixed;

    //Location
    glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * mat;
    file << std::setprecision(precision) << xyzw.x <<" "<< xyzw.y <<" "<< xyzw.z ;

    //Intensity
    if(vec_I.size() != 0){
      file << std::setprecision(0) <<" "<< int(vec_I[i] * 255);
    }

    //Color
    if(data->rgb.size() != 0){
      glm::vec3 RGB = use_rgba ? glm::vec3(rgba[i].x, rgba[i].y, rgba[i].z) : rgb[i];
      file << std::setprecision(0) <<" "<< RGB.x * 255 <<" "<< RGB.y * 255 <<" "<< RGB.z * 255;
    }

    //Normal
    if(data->Nxyz.size() != 0){
      file << std::setprecision(precision) <<" "<< N[i].x <<" "<< N[i].y <<" "<< N[i].z;
    }

    //line end
    file << std::endl;
  }

  //---------------------------
  file.close();
}



}
