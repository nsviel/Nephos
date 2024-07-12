#include "Exporter.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace fmt::ply{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->ldr_header = new fmt::ply::exporter::Header();

  this->format = ".ply";
  this->vec_encoding.push_back(ldr::io::ASCII);
  this->vec_encoding.push_back(ldr::io::BINARY);

  //---------------------------
}
Exporter::~Exporter(){}

//Main exporter functions
void Exporter::export_ascii(utl::base::Data* data, glm::mat4 mat, std::string path){
  std::string encoding = "ascii";
  //---------------------------

  std::ofstream file(path);

  fmt::ply::exporter::Structure exporter;
  this->build_structure(exporter, data, encoding);
  this->write_header(file, encoding, data);
  this->write_data_ascii(file, data, mat);

  file.close();

  //---------------------------
}
void Exporter::export_binary(utl::base::Data* data, glm::mat4 mat, std::string path){
  std::string encoding = "binary_little_endian";
  //---------------------------

  std::ofstream file(path, std::ios::binary);

  fmt::ply::exporter::Structure exporter;
  this->build_structure(exporter, data, encoding);
  this->write_header(file, encoding, data);
  this->write_data_binary(file, data, mat);

  file.close();

  //---------------------------
}

//Subfunction
void Exporter::build_structure(fmt::ply::exporter::Structure& exporter, utl::base::Data* data, std::string encoding){
  //---------------------------

  exporter.nb_vertex = (data->size > 0) ? data->size : data->xyz.size();
  exporter.encoding = encoding;

  if(data->xyz.size() != 0){
    exporter.vec_property.push_back(fmt::ply::XYZ);
    exporter.nb_property += 3;
  }
  if(data->rgb.size() != 0){
    exporter.vec_property.push_back(fmt::ply::RGB);
    exporter.nb_property += 3;
  }
  if(data->Nxyz.size() != 0){
    exporter.vec_property.push_back(fmt::ply::NXYZ);
    exporter.nb_property += 3;
  }
  if(data->Is.size() != 0){
    exporter.vec_property.push_back(fmt::ply::I);
    exporter.nb_property++;
  }
  if(data->ts.size() != 0){
    exporter.vec_property.push_back(fmt::ply::TS);
    exporter.nb_property++;
  }

  //---------------------------
}
void Exporter::write_header(std::ofstream& file, std::string format, utl::base::Data* data){
  //---------------------------



  this->vec_property.clear();

  //Write header
  file << "ply" << std::endl;
  file << "format " + format + " 1.0" << std::endl;
  int nb_vertex = (data->size > 0) ? data->size : data->xyz.size();
  file << "element vertex " << nb_vertex << std::endl;

  file << "property float32 x" << std::endl;
  file << "property float32 y" << std::endl;
  file << "property float32 z" << std::endl;
  vec_property.push_back(fmt::ply::XYZ);
  this->property_number = 3;

  if(data->rgb.size() != 0){
    file << "property uchar red" << std::endl;
    file << "property uchar green" << std::endl;
    file << "property uchar blue" << std::endl;

    vec_property.push_back(fmt::ply::RGB);
    this->property_number += 3;
  }
  if(data->Nxyz.size() != 0){
    file << "property float32 nx" << std::endl;
    file << "property float32 ny" << std::endl;
    file << "property float32 nz" << std::endl;

    vec_property.push_back(fmt::ply::NXYZ);
    this->property_number += 3;
  }
  if(data->Is.size() != 0){
    file << "property float32 intensity" << std::endl;

    vec_property.push_back(fmt::ply::I);
    property_number++;
  }
  if(data->ts.size() != 0){
    file << "property float32 timestamp" << std::endl;

    vec_property.push_back(fmt::ply::TS);
    property_number++;
  }
  file << "end_header" <<std::endl;

  //---------------------------
}
void Exporter::write_data_ascii(std::ofstream& file, utl::base::Data* data, glm::mat4& mat){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& Is = data->Is;
  int precision = 6;

  //Write data in the file
  for(int i=0; i<xyz.size(); i++){
    file << std::fixed;

    //Location
    glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * mat;
    file << std::setprecision(precision) << xyzw.x <<" "<< xyzw.y <<" "<< xyzw.z <<" ";

    //Color
    if(rgb.size() != 0){
      glm::vec3 RGB = use_rgba ? glm::vec3(rgba[i].x, rgba[i].y, rgba[i].z) : rgb[i];
      file << std::setprecision(0) << RGB.x * 255 <<" "<< RGB.y * 255 <<" "<< RGB.z * 255 <<" ";
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
void Exporter::write_data_binary(std::ofstream& file, utl::base::Data* data, glm::mat4& mat){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
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
    for(int j=0; j<property_number; j++){

      switch(vec_property[j]){
        //Location
        case fmt::ply::XYZ:{
          glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * mat;
          memcpy(block_data + offset, &xyzw, sizeof(glm::vec3));
          offset += sizeof(glm::vec3);
          break;
        }

        //Color
        case fmt::ply::RGB:{
          for(int k=0; k<3; k++){
            glm::vec3 RGB = use_rgba ? glm::vec3(rgba[i].x, rgba[i].y, rgba[i].z) : rgb[i];
            int color_int = RGB[k] * 255;
            memcpy(block_data + offset, &color_int, sizeof(u_char));
            offset += sizeof(u_char);
          }
          break;
        }

        //Intensity
        case fmt::ply::I:{
          memcpy(block_data + offset, &Is[i], sizeof(float));
          offset += sizeof(float);
          break;
        }

        //Normal
        case fmt::ply::NXYZ:{
          memcpy(block_data + offset, &Nxyz[i], sizeof(glm::vec3));
          offset += sizeof(glm::vec3);
          break;
        }

        //Timestamp
        case fmt::ply::TS:{
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
