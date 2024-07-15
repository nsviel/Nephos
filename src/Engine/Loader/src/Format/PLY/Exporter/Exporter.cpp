#include "Exporter.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace fmt::ply{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->ldr_header = new fmt::ply::exporter::Header();
  this->utl_attribut = new utl::base::Attribut();

  this->format = ".ply";
  this->vec_encoding.push_back(ldr::exporter::ASCII);
  this->vec_encoding.push_back(ldr::exporter::BINARY);

  //---------------------------
}
Exporter::~Exporter(){}

//Main exporter functions
void Exporter::export_data(ldr::exporter::Configuration& config, utl::base::Data* data){
  //---------------------------
/*
  //Make exporter structure
  fmt::ply::exporter::Structure exporter;
  exporter.mat_model = config.mat_model;
  exporter.mat_rotation = glm::mat3(config.mat_model);
  this->build_structure(exporter, data);

  //Write on file
  switch(config.encoding){
    case ldr::exporter::ASCII:{
      exporter.encoding = "ascii";
      std::ofstream file(path);
      ldr_header->write_header(exporter, file);
      this->write_data_ascii(exporter, file, data);
      file.close();
      break;
    }
    case ldr::exporter::BINARY:{
      exporter.encoding = "binary_little_endian";
      std::ofstream file(path, std::ios::binary);
      ldr_header->write_header(exporter, file);
      this->write_data_binary(exporter, file, data);
      file.close();
      break;
    }
  }
*/
  //---------------------------
}

//Subfunction
void Exporter::build_structure(fmt::ply::exporter::Structure& exporter, utl::base::Data* data){
  //---------------------------

  exporter.nb_vertex = (data->size > 0) ? data->size : data->xyz.size();

  //Location
  if(data->xyz.size() != 0){
    exporter.vec_property.push_back(fmt::ply::XYZ);
    exporter.nb_property += 3;
  }

  //Color
  if(data->rgb.size() != 0){
    exporter.vec_property.push_back(fmt::ply::RGB);
    exporter.nb_property += 3;
  }

  //Normal
  if(data->Nxyz.size() != 0){
    exporter.vec_property.push_back(fmt::ply::NXYZ);
    exporter.nb_property += 3;
  }

  //Intensity
  std::vector<float>& vec_I = utl_attribut->get_attribut_data(data, "I");
  if(vec_I.size() != 0){
    exporter.vec_property.push_back(fmt::ply::I);
    exporter.nb_property++;
  }

  //Timestamp
  std::vector<float>& vec_ts = utl_attribut->get_attribut_data(data, "ts");
  if(vec_ts.size() != 0){
    exporter.vec_property.push_back(fmt::ply::TS);
    exporter.nb_property++;
  }

  //---------------------------
}
void Exporter::write_data_ascii(fmt::ply::exporter::Structure& exporter, std::ofstream& file, utl::base::Data* data){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& vec_I = utl_attribut->get_attribut_data(data, "I");
  int precision = 6;

  //Write data in the file
  for(int i=0; i<xyz.size(); i++){
    file << std::fixed;

    //Location
    glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * exporter.mat_model;
    file << std::setprecision(precision) << xyzw.x <<" "<< xyzw.y <<" "<< xyzw.z <<" ";

    //Color
    if(!use_rgba && rgb.size() != 0){
      glm::vec3& RGB = rgb[i];
      file << std::setprecision(0) << RGB.x * 255 <<" "<< RGB.y * 255 <<" "<< RGB.z * 255 <<" ";
    }else if(use_rgba && rgba.size() != 0){
      glm::vec4& RGBA = rgba[i];
      file << std::setprecision(0) << RGBA.x * 255 <<" "<< RGBA.y * 255 <<" "<< RGBA.z * 255 <<" ";
    }

    //Normal
    if(Nxyz.size() != 0){
      glm::vec3 normal = Nxyz[i] * exporter.mat_rotation;
      file << std::setprecision(precision) << normal.x <<" "<< normal.y <<" "<< normal.z <<" ";
    }

    //Intensity
    if(vec_I.size() != 0){
      file << std::setprecision(precision) << vec_I[i] << " ";
    }

    file << std::endl;
  }

  //---------------------------
}
void Exporter::write_data_binary(fmt::ply::exporter::Structure& exporter, std::ofstream& file, utl::base::Data* data){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& vec_I = utl_attribut->get_attribut_data(data, "I");
  std::vector<float>& vec_ts = utl_attribut->get_attribut_data(data, "ts");
  int precision = 6;

  //Prepare data writing by blocks
  int block_size = exporter.nb_property * xyz.size() * sizeof(float);
  char* block_data = new char[block_size];

  //Convert decimal data into binary data
  int offset = 0;
  int cpt_property = 0;
  for(int i=0; i<xyz.size(); i++){
    for(int j=0; j<exporter.vec_property.size(); j++){
      fmt::ply::Field& field = exporter.vec_property[j];

      switch(field){
        //Location
        case fmt::ply::XYZ:{
          glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * exporter.mat_model;
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
          memcpy(block_data + offset, &vec_I[i], sizeof(float));
          offset += sizeof(float);
          break;
        }

        //Normal
        case fmt::ply::NXYZ:{
          glm::vec3 normal = Nxyz[i] * exporter.mat_rotation;
          memcpy(block_data + offset, &normal, sizeof(glm::vec3));
          offset += sizeof(glm::vec3);
          break;
        }

        //Timestamp
        case fmt::ply::TS:{
          memcpy(block_data + offset, &vec_ts[i], sizeof(float));
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
