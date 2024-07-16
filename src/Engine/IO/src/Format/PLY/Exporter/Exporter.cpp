#include "Exporter.h"

#include <IO/Namespace.h>
#include <Utility/Namespace.h>


namespace fmt::ply{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->io_header = new fmt::ply::exporter::Header();
  this->utl_attribut = new utl::base::Attribut();

  this->format = ".ply";
  this->vec_encoding.push_back(io::exporter::ASCII);
  this->vec_encoding.push_back(io::exporter::BINARY);

  //---------------------------
}
Exporter::~Exporter(){}

//Main exporter functions
void Exporter::export_data(io::exporter::Configuration& config, utl::base::Data* data){
  //---------------------------
/*
  //Make exporter structure
  io::exporter::Configuration config;
  config.mat_model = config.mat_model;
  config.mat_rotation = glm::mat3(config.mat_model);
  this->build_structure(config, data);

  //Write on file
  switch(config.encoding){
    case io::exporter::ASCII:{
      config.encoding = "ascii";
      std::ofstream file(path);
      io_header->write_header(config, file);
      this->write_data_ascii(config, file, data);
      file.close();
      break;
    }
    case io::exporter::BINARY:{
      config.encoding = "binary_little_endian";
      std::ofstream file(path, std::ios::binary);
      io_header->write_header(config, file);
      this->write_data_binary(config, file, data);
      file.close();
      break;
    }
  }
*/
  //---------------------------
}

//Subfunction
void Exporter::build_structure(io::exporter::Configuration& config, utl::base::Data* data){
  //---------------------------

  config.nb_vertex = (data->size > 0) ? data->size : data->xyz.size();

  //Location
  if(data->xyz.size() != 0){
    config.vec_property.push_back(io::exporter::XYZ);
    config.nb_property += 3;
  }

  //Color
  if(data->rgb.size() != 0){
    config.vec_property.push_back(io::exporter::RGB);
    config.nb_property += 3;
  }

  //Normal
  if(data->Nxyz.size() != 0){
    config.vec_property.push_back(io::exporter::NXYZ);
    config.nb_property += 3;
  }

  //Intensity
  std::vector<float>& vec_I = utl_attribut->get_field_data(data, "I");
  if(vec_I.size() != 0){
    config.vec_property.push_back(io::exporter::I);
    config.nb_property++;
  }

  //Timestamp
  std::vector<float>& vec_ts = utl_attribut->get_field_data(data, "ts");
  if(vec_ts.size() != 0){
    config.vec_property.push_back(io::exporter::TS);
    config.nb_property++;
  }

  //---------------------------
}
void Exporter::write_data_ascii(io::exporter::Configuration& config, std::ofstream& file, utl::base::Data* data){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& vec_I = utl_attribut->get_field_data(data, "I");
  int precision = 6;

  //Write data in the file
  for(int i=0; i<xyz.size(); i++){
    file << std::fixed;

    //Location
    glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * config.mat_model;
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
      glm::vec3 normal = Nxyz[i] * config.mat_rotation;
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
void Exporter::write_data_binary(io::exporter::Configuration& config, std::ofstream& file, utl::base::Data* data){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& vec_I = utl_attribut->get_field_data(data, "I");
  std::vector<float>& vec_ts = utl_attribut->get_field_data(data, "ts");
  int precision = 6;

  //Prepare data writing by blocks
  int block_size = config.nb_property * xyz.size() * sizeof(float);
  char* block_data = new char[block_size];

  //Convert decimal data into binary data
  int offset = 0;
  int cpt_property = 0;
  for(int i=0; i<xyz.size(); i++){
    for(int j=0; j<config.vec_property.size(); j++){
      io::exporter::Field& field = config.vec_property[j];

      switch(field){
        //Location
        case io::exporter::XYZ:{
          glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * config.mat_model;
          memcpy(block_data + offset, &xyzw, sizeof(glm::vec3));
          offset += sizeof(glm::vec3);
          break;
        }

        //Color
        case io::exporter::RGB:{
          for(int k=0; k<3; k++){
            glm::vec3 RGB = use_rgba ? glm::vec3(rgba[i].x, rgba[i].y, rgba[i].z) : rgb[i];
            int color_int = RGB[k] * 255;
            memcpy(block_data + offset, &color_int, sizeof(u_char));
            offset += sizeof(u_char);
          }
          break;
        }

        //Intensity
        case io::exporter::I:{
          memcpy(block_data + offset, &vec_I[i], sizeof(float));
          offset += sizeof(float);
          break;
        }

        //Normal
        case io::exporter::NXYZ:{
          glm::vec3 normal = Nxyz[i] * config.mat_rotation;
          memcpy(block_data + offset, &normal, sizeof(glm::vec3));
          offset += sizeof(glm::vec3);
          break;
        }

        //Timestamp
        case io::exporter::TS:{
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
