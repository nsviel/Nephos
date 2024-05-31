#include "Exporter.h"

#include <Data/Namespace.h>
#include <Utility/Function/File/File.h>


namespace format::pts{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->format = "pts";

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::export_ascii(utl::base::Data* data, utl::base::Pose* pose, std::string path){
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
  std::vector<glm::vec3>& N = data->Nxyz;
  std::vector<float>& Is = data->Is;

  //Write in the file
  int precision = 6;
  file << xyz.size() << std::endl;
  for(int i=0; i<xyz.size(); i++){
    //Line start
    file << std::fixed;

    //Location
    file << std::setprecision(precision) << xyz[i].x <<" "<< xyz[i].y <<" "<< xyz[i].z ;

    //Intensity
    if(data->Is.size() != 0){
      file << std::setprecision(0) <<" "<< int(Is[i] * 255);
    }

    //Color
    if(data->rgb.size() != 0){
      file << std::setprecision(0) <<" "<< rgb[i].x * 255 <<" "<< rgb[i].y * 255 <<" "<< rgb[i].z * 255;
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
