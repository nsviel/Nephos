#include "Importer.h"

#include <Element/Namespace.h>
#include <IO/Namespace.h>
#include <Utility/Function/File/File.h>


namespace fmt::pts{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->utl_attribut = new utl::base::Attribut();

  this->Is_format = fmt::pts::F2048_2048;
  this->format = ".pts";

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::base::Element* Importer::import(utl::base::Path path){
  //---------------------------

  //Init
  dat::base::Object* object = new dat::base::Object();
  object->name = path.name;
  object->data.name = path.name;
  object->data.path = path;
  object->data.path.format = format;
  object->data.topology.type = utl::topology::POINT;

  //Initialization
  io::imp::Configuration config;
  config.path = path.build();

  //Processing
  this->retrieve_header(config);
  this->retrieve_size(config);
  this->retrieve_configuration(config);
  this->retrieve_data(config);
  this->transfer_data(config, &object->data);

  //---------------------------
  return object;
}

//Subfunction
void Importer::retrieve_header(io::imp::Configuration& config){
  //---------------------------

  std::vector<float> vec_data = retrieve_column(config, 1);
  if(vec_data.size() <= 1){
    config.has_header = true;
  }else{
    config.has_header = false;
  }

  //---------------------------
}
void Importer::retrieve_size(io::imp::Configuration& config){
  //---------------------------

  config.nb_vertex = utl::file::number_point(config.path);
  if(config.has_header) config.nb_vertex -= 1;

  //---------------------------
}
void Importer::retrieve_configuration(io::imp::Configuration& config){
  //---------------------------

  std::vector<float> vec_data = retrieve_column(config, 5);

  switch(vec_data.size()){
    case 3 :{ // XYZ
      config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
      break;
    }
    case 4 :{ // XYZI
      config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
      config.vec_property.push_back(io::imp::Property(io::imp::I));
      break;
    }
    case 6 :{
      float R =vec_data[3];
      float G =vec_data[4];
      float B =vec_data[5];

      //xyz - N
      bool color = abs(R) <= 1 && abs(G) <= 1 && abs(B) <= 1;
      bool nan = std::isnan(R) && std::isnan(G) && std::isnan(B);
      if(color || nan){
        config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::NXYZ));
      }

      //xyz - rgb
      bool empty = abs(R) == 0 && abs(G) == 0 && abs(B) == 0;
      bool normal = abs(R) >= 1 && abs(G) >= 1 && abs(B) >= 1;
      if(empty || normal){
        config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::RGB));
      }
      break;
    }
    case 7 :{
      float I =vec_data[3];
      float R =vec_data[4];
      float G =vec_data[5];
      float B =vec_data[6];

      //xyz - I - rgb
      bool empty = abs(I) == 0 && abs(R) == 0 && abs(G) == 0 && abs(B) == 0;
      bool full = abs(I) >= 1 && abs(R) >= 1 && abs(G) >= 1 && abs(B) >= 1;
      if(empty || full){
        config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::RGB));
        break;
      }

      //xyz - I - N
      bool normal = abs(R) <= 1.1f && abs(G) <= 1.1 && abs(B) <= 1.1;
      bool nan = std::isnan(R) && std::isnan(G) && std::isnan(B);
      if(normal || nan){
        config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::I));
        config.vec_property.push_back(io::imp::Property(io::imp::NXYZ));
        break;
      }

      //xyz - rgb - I01
      bool a1 = I >= 0 && I <= 255;
      bool a2 = R >= 0 && R <= 255;
      bool a3 = G >= 0 && G <= 255;
      bool a4 = B >= 0 && B <= 1;
      if(a1 && a2 && a3 && a4){
        config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::RGB));
        config.vec_property.push_back(io::imp::Property(io::imp::I));
        Is_format = fmt::pts::F0_1;
        break;
      }

      //xyz - I01 - RBG
      bool b1 = I >= 0 && I <= 1;
      bool b2 = R >= 0 && R <= 255;
      bool b3 = G >= 0 && G <= 255;
      bool b4 = B >= 0 && B <= 255;
      if(b1 && b2 && b3 && b4){
        config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::I));
        config.vec_property.push_back(io::imp::Property(io::imp::RGB));
        Is_format = fmt::pts::F0_1;
        break;
      }
      break;
    }
    case 9 :{ //xyz - rgb - N
      config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
      config.vec_property.push_back(io::imp::Property(io::imp::RGB));
      config.vec_property.push_back(io::imp::Property(io::imp::NXYZ));
      break;
    }
    case 10 :{
      //xyz - rgb - N - I[0;1]
      if(vec_data[3] >= 1 && vec_data[3] <= 255 && abs(vec_data[6]) >= 0 && abs(vec_data[6]) <= 1 ){
        config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::RGB));
        config.vec_property.push_back(io::imp::Property(io::imp::NXYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::I));
        Is_format = fmt::pts::F0_1;
        break;
      }
      //xyz - rgb - N - I[-2048;+2047]
      else if(vec_data[3] >= 1 && vec_data[3] <= 255 && abs(vec_data[6]) > 1 && abs(vec_data[6]) <= 2048 ){
        config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::RGB));
        config.vec_property.push_back(io::imp::Property(io::imp::NXYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::I));
        Is_format = fmt::pts::F2048_2048;
        break;
      }
      else{//xyz - I - rgb - N
        config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
        config.vec_property.push_back(io::imp::Property(io::imp::I));
        config.vec_property.push_back(io::imp::Property(io::imp::RGB));
        config.vec_property.push_back(io::imp::Property(io::imp::NXYZ));

        float I =vec_data[3];
        bool Isc1 = abs(I) >= 0 && abs(I) <= 1;
        if(Isc1){
          Is_format = fmt::pts::F0_1;
        }
      }
      break;
    }
    default :{  // xyz - rgb
      config.vec_property.push_back(io::imp::Property(io::imp::XYZ));
      config.vec_property.push_back(io::imp::Property(io::imp::RGB));
    }
  }

  //---------------------------
}
void Importer::retrieve_data(io::imp::Configuration& config){
  this->buffer = {};
  //---------------------------

  //Read file
  std::ifstream file(config.path);
  std::string line;
  if(config.has_header) std::getline(file, line);

  //Data
  while(std::getline(file, line)){
    //If line empty break the while
    if(line.empty()){
      break;
    }

    float d;
    std::istringstream iss(line);
    for(int i=0; i<config.vec_property.size(); i++){
      io::imp::Property& property = config.vec_property[i];

      switch(property.field){
        case io::imp::XYZ:{
          float x, y, z;
          iss >> x;
          iss >> y;
          iss >> z;
          buffer.xyz.push_back(glm::vec3(x, y, z));
          break;
        }
        case io::imp::NXYZ:{
          float nx, ny, nz;
          iss >> nx;
          iss >> ny;
          iss >> nz;
          buffer.Nxyz.push_back(glm::vec3(nx, ny, nz));
          break;
        }
        case io::imp::RGB:{
          float r, g, b;
          iss >> r;
          iss >> g;
          iss >> b;
          buffer.rgb.push_back(glm::vec3(r/255, g/255, b/255));
          break;
        }
        case io::imp::I:{
          float I;
          iss >> I;

          switch(Is_format){
            case fmt::pts::F0_255:{
              I /= 255;
              break;
            }
            case fmt::pts::F2048_2048:{
              I = (I + 2048) / 4096;
              break;
            }
          }

          buffer.Is.push_back(I);
          break;
        }
      }
    }
  }

  //---------------------------
}
void Importer::transfer_data(io::imp::Configuration& config, utl::base::Data* data){
  //---------------------------

  data->xyz = buffer.xyz;
  data->Nxyz = buffer.Nxyz;
  data->rgb = buffer.rgb;
  data->size = buffer.xyz.size();
  utl_attribut->set_field_data(data, "I", buffer.Is);

  //---------------------------
}
std::vector<float> Importer::retrieve_column(io::imp::Configuration& config, int idx){
  //---------------------------

  //Get first line
  std::string line;
  std::ifstream file(config.path);

  for(int i=0; i<idx; i++){
    getline(file, line);
  }

  //Column count
  std::vector<float> vec_data;
  bool end_loop = false;
  while(!end_loop){
    if(line.find(" ") != std::string::npos){
      vec_data.push_back(std::stof(line.substr(0, line.find(" "))));
      line = line.substr(line.find(" ")+1);
    }else{
      vec_data.push_back(std::stof(line));
      end_loop = true;
    }
  }

  //---------------------------
  return vec_data;
}

}
