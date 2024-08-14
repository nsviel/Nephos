#include "Exporter.h"

#include <Element/Namespace.h>
#include <Utility/Function/File/File.h>


namespace fmt::pts{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->utl_attribut = new utl::base::Attribut();

  this->format = ".pts";
  this->vec_encoding.push_back(io::exporter::ASCII);

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::export_data(io::exporter::Configuration& config, utl::base::Data* data){
  //---------------------------

  this->write_data_ascii(config, data);

  //---------------------------
}

//Subfunction
void Exporter::write_data_ascii(io::exporter::Configuration& config, utl::base::Data* data){
  //---------------------------

  //Create file
  std::ofstream file;
  file.open(config.path);
  if(!file){
    std::cout<<"Error in creating file !";
    return;
  }

  //Data : xyz (R) (rgb) (nxnynz)
  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& vec_I = utl_attribut->get_field_data(data, "I");

  //Write in the file
  int precision = 6;
  file << xyz.size() << std::endl;
  for(int i=0; i<xyz.size(); i++){
    //Line start
    file << std::fixed;

    //Location
    glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * config.mat_model;
    file << std::setprecision(precision) << xyzw.x <<" "<< xyzw.y <<" "<< xyzw.z ;

    //Intensity
    if(vec_I.size() != 0){
      file << std::setprecision(0) <<" "<< int(vec_I[i] * 255);
    }

    //Color
    if(data->rgb.size() != 0){
      glm::vec3 RGB = config.with_colorization ? glm::vec3(rgba[i].x, rgba[i].y, rgba[i].z) : rgb[i];
      file << std::setprecision(0) <<" "<< RGB.x * 255 <<" "<< RGB.y * 255 <<" "<< RGB.z * 255;
    }

    //Normal
    if(data->Nxyz.size() != 0){
      glm::vec3 normal = Nxyz[i] * config.mat_rotation;
      file << std::setprecision(precision) <<" "<< normal.x <<" "<< normal.y <<" "<< normal.z;
    }

    //line end
    file << std::endl;
  }

  //---------------------------
  file.close();
}

}
