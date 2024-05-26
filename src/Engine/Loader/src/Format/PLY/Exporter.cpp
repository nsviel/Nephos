#include "Exporter.h"

#include <Utility/Namespace.h>


namespace format::ply{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->format = "ply";

  //---------------------------
}
Exporter::~Exporter(){}

//Main exporter functions
void Exporter::export_ascii(utl::base::Data* data, std::string path){
  std::string format = "ascii";
  //---------------------------

  std::ofstream file(path);

  this->write_header(file, format, data);
  this->write_data_ascii(file, data);

  file.close();

  //---------------------------
}
void Exporter::export_binary(utl::base::Data* data, utl::base::Pose* pose, std::string path){
  std::string format = "binary_little_endian";
  //---------------------------

  std::ofstream file(path, std::ios::binary);

  this->write_header(file, format, data);
  this->write_data_binary(file, data, pose);

  file.close();

  //---------------------------
}

//Subfunction
void Exporter::write_header(std::ofstream& file, std::string format, utl::base::Data* data){
  //---------------------------

  this->vec_property.clear();

  //Write header
  file << "ply" << std::endl;
  file << "format " + format + " 1.0" << std::endl;
  file << "element vertex " << data->size << std::endl;

  file << "property float32 x" << std::endl;
  file << "property float32 y" << std::endl;
  file << "property float32 z" << std::endl;
  vec_property.push_back(format::ply::X);
  vec_property.push_back(format::ply::VOID);
  vec_property.push_back(format::ply::VOID);
  this->property_number = 3;

  if(data->rgb.size() != 0){
    file << "property uchar red" << std::endl;
    file << "property uchar green" << std::endl;
    file << "property uchar blue" << std::endl;

    vec_property.push_back(format::ply::R);
    vec_property.push_back(format::ply::VOID);
    vec_property.push_back(format::ply::VOID);
    this->property_number += 3;
  }
  if(data->Nxyz.size() != 0){
    file << "property float32 nx" << std::endl;
    file << "property float32 ny" << std::endl;
    file << "property float32 nz" << std::endl;

    vec_property.push_back(format::ply::NX);
    vec_property.push_back(format::ply::VOID);
    vec_property.push_back(format::ply::VOID);
    this->property_number += 3;
  }
  if(data->Is.size() != 0){
    file << "property float32 scalar_field" << std::endl;

    vec_property.push_back(format::ply::I);
    property_number++;
  }
  if(data->ts.size() != 0){
    file << "property float32 timestamp" << std::endl;

    vec_property.push_back(format::ply::TS);
    property_number++;
  }
  file << "end_header" <<std::endl;

  //---------------------------
}
void Exporter::write_data_ascii(std::ofstream& file, utl::base::Data* data){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec4>& rgb = data->rgb;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& Is = data->Is;
  int precision = 6;

  //Write data in the file
  for(int i=0; i<xyz.size(); i++){
    file << std::fixed;

    //Location
    file << std::setprecision(precision) << xyz[i].x <<" "<< xyz[i].y <<" "<< xyz[i].z <<" ";

    //Color
    if(rgb.size() != 0){
      file << std::setprecision(0) << rgb[i].x * 255 <<" "<< rgb[i].y * 255 <<" "<< rgb[i].z * 255 <<" ";
    }

    //Normal
    if(Nxyz.size() != 0){
      file << std::setprecision(precision) << Nxyz[i].x <<" "<< Nxyz[i].y <<" "<< Nxyz[i].z <<" ";
    }

    //Intensity
    if(Is.size() != 0){
      file << std::setprecision(precision) << Is[i] << " ";
    }

    file << std::endl;
  }

  //---------------------------
}
void Exporter::write_data_binary(std::ofstream& file, utl::base::Data* data, utl::base::Pose* pose){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec4>& rgb = data->rgb;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& Is = data->Is;
  std::vector<float>& ts = data->ts;
  int precision = 6;

  //Prepare data writing by blocks
  int block_size = property_number * xyz.size() * sizeof(float);
  char* block_data = new char[block_size];

  //Convert decimal data into binary data
  int offset = 0;
  int cpt_property = 0;
  for(int i=0; i<xyz.size(); i++){
    for (int j=0; j<property_number; j++){

      switch(vec_property[j]){
        //Location
        case format::ply::X:{
          glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * pose->model;
          memcpy(block_data + offset, &xyzw, sizeof(glm::vec3));
          offset += sizeof(glm::vec3);
          break;
        }

        //Color
        case format::ply::R:{
          for(int k=0; k<3; k++){
            int color_int = rgb[i][k] * 255;
            memcpy(block_data + offset, &color_int, sizeof(u_char));
            offset += sizeof(u_char);
          }
          break;
        }

        //Intensity
        case format::ply::I:{
          memcpy(block_data + offset, &Is[i], sizeof(float));
          offset += sizeof(float);
          break;
        }

        //Normal
        case format::ply::NX:{
          memcpy(block_data + offset, &Nxyz[i], sizeof(glm::vec3));
          offset += sizeof(glm::vec3);
          break;
        }

        //Timestamp
        case format::ply::TS:{
          memcpy(block_data + offset, &ts[i], sizeof(float));
          offset += sizeof(float);
          break;
        }
      }

    }
  }

  //Read all data blocks & read the last data block
  file.write(block_data, block_size);

  //---------------------------
}

}
