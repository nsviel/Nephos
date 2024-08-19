#include "Exporter.h"
#include "Header.h"

#include <Utility/Namespace.h>


namespace fmt::ply{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->io_header = new fmt::ply::exporter::Header();
  this->atr_field = new dat::atr::Field();

  this->format = ".ply";
  this->vec_encoding.push_back(io::exp::ASCII);
  this->vec_encoding.push_back(io::exp::BINARY);

  //---------------------------
}
Exporter::~Exporter(){}

//Main exporter functions
void Exporter::export_data(io::exp::Configuration& config, utl::base::Data* data){
  //---------------------------

  //Make exporter structure
  this->build_structure(config, data);

  //Write on file
  switch(config.encoding){
    case io::exp::ASCII:{
      config.format = "ascii";
      std::ofstream file(config.path);
      io_header->write_header(config, file);
      this->write_data_ascii(config, file, data);
      file.close();
      break;
    }
    case io::exp::BINARY:{
      config.format = "binary_little_endian";
      std::ofstream file(config.path, std::ios::binary);
      io_header->write_header(config, file);
      this->write_data_binary(config, file, data);
      file.close();
      break;
    }
  }

  //---------------------------
}

//Subfunction
void Exporter::build_structure(io::exp::Configuration& config, utl::base::Data* data){
  //---------------------------

  config.nb_vertex = (data->size > 0) ? data->size : data->xyz.size();

  //Location
  if(data->xyz.size() != 0){
    config.vec_property.push_back(io::exp::XYZ);
    config.nb_property += 3;
  }

  //Color
  if(config.with_colorization && data->rgba.size() != 0){
    config.vec_property.push_back(io::exp::RGB);
    config.nb_property += 3;
  }
  else if(!config.with_colorization && data->rgb.size() != 0){
    config.vec_property.push_back(io::exp::RGB);
    config.nb_property += 3;
  }

  //Normal
  if(data->Nxyz.size() != 0){
    config.vec_property.push_back(io::exp::NXYZ);
    config.nb_property += 3;
  }

  //Intensity
  std::vector<float>& vec_I = atr_field->get_field_data(data, "I");
  if(vec_I.size() != 0){
    config.vec_property.push_back(io::exp::I);
    config.nb_property++;
  }

  //Timestamp
  std::vector<float>& vec_ts = atr_field->get_field_data(data, "ts");
  if(vec_ts.size() != 0){
    config.vec_property.push_back(io::exp::TS);
    config.nb_property++;
  }

  //---------------------------
}
void Exporter::write_data_ascii(io::exp::Configuration& config, std::ofstream& file, utl::base::Data* data){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& vec_I = atr_field->get_field_data(data, "I");
  int precision = 6;

  //Write data in the file
  for(int i=0; i<xyz.size(); i++){
    file << std::fixed;

    //Location
    glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * config.mat_model;
    file << std::setprecision(precision) << xyzw.x <<" "<< xyzw.y <<" "<< xyzw.z <<" ";

    //Color
    if(!config.with_colorization && rgb.size() != 0){
      glm::vec3& RGB = rgb[i];
      file << std::setprecision(0) << RGB.x * 255 <<" "<< RGB.y * 255 <<" "<< RGB.z * 255 <<" ";
    }else if(config.with_colorization && rgba.size() != 0){
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
void Exporter::write_data_binary(io::exp::Configuration& config, std::ofstream& file, utl::base::Data* data){
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& rgb = data->rgb;
  std::vector<glm::vec4>& rgba = data->rgba;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  std::vector<float>& vec_I = atr_field->get_field_data(data, "I");
  std::vector<float>& vec_ts = atr_field->get_field_data(data, "ts");
  int precision = 6;

  //Prepare data writing by blocks
  int block_size = config.nb_property * xyz.size() * sizeof(float);
  char* block_data = new char[block_size];

  //Convert decimal data into binary data
  int offset = 0;
  int cpt_property = 0;
  for(int i=0; i<xyz.size(); i++){
    for(int j=0; j<config.vec_property.size(); j++){
      io::exp::Field& field = config.vec_property[j];

      switch(field){
        //Location
        case io::exp::XYZ:{
          glm::vec4 xyzw = glm::vec4(xyz[i], 1.0) * config.mat_model;
          memcpy(block_data + offset, &xyzw, sizeof(glm::vec3));
          offset += sizeof(glm::vec3);
          break;
        }

        //Color
        case io::exp::RGB:{
          glm::vec3 RGB = config.with_colorization ? glm::vec3(rgba[i].x, rgba[i].y, rgba[i].z) : rgb[i];
          for(int k=0; k<3; k++){
            int RGB_int = RGB[k] * 255;
            memcpy(block_data + offset, &RGB_int, sizeof(u_char));
            offset += sizeof(u_char);
          }
          break;
        }

        //Intensity
        case io::exp::I:{
          memcpy(block_data + offset, &vec_I[i], sizeof(float));
          offset += sizeof(float);
          break;
        }

        //Normal
        case io::exp::NXYZ:{
          glm::vec3 normal = Nxyz[i] * config.mat_rotation;
          memcpy(block_data + offset, &normal, sizeof(glm::vec3));
          offset += sizeof(glm::vec3);
          break;
        }

        //Timestamp
        case io::exp::TS:{
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
