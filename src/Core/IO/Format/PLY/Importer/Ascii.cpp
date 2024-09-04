#include "Ascii.h"

#include <Data/Namespace.h>


namespace fmt::ply::importer{

//Constructor / Destructor
Ascii::Ascii(){
  //---------------------------

  this->atr_field = new dat::atr::Field();

  //---------------------------
}
Ascii::~Ascii(){}

//Main function
void Ascii::parse_ascii(io::imp::Configuration* config, std::shared_ptr<dat::base::Object> object){
  //---------------------------

  //Open file
  std::ifstream file(config->path);
  this->pass_header(file);

  //Read data
  this->parse_vertex(config, file);
  this->parse_face(config, file);

  //Store result
  object->data->xyz = buffer.xyz;
  object->data->Nxyz = buffer.Nxyz;
  object->data->rgb = buffer.rgb;
  object->data->size = buffer.xyz.size();
  atr_field->set_field_data(*object->data, "I", buffer.Is);

  //Close file
  file.close();

  //---------------------------
}

//Subfunction
void Ascii::pass_header(std::ifstream& file){
  std::string line;
  //---------------------------

  while(std::getline(file, line)){
    if(line == "end_header"){
      break;
    }
  }

  //---------------------------
}
void Ascii::parse_vertex(io::imp::Configuration* config, std::ifstream& file){
  this->buffer = {};
  //---------------------------

  //Retrieve vertex data
  std::string line;
  for(int i=0; i<config->nb_vertex; i++){
    //Data
    std::getline(file, line);
    std::istringstream iss(line);
    std::vector<float> row;
    for(int i=0; i<config->vec_property.size(); i++){
      float d;
      iss >> d;
      row.push_back(d);
    }

    //Location
    int id_x = get_property_id(config, io::imp::XYZ);
    if(id_x != -1){
      buffer.xyz.push_back(glm::vec3(row[id_x], row[id_x+1], row[id_x+2]));
    }

    //Normal
    int id_nx = get_property_id(config, io::imp::NXYZ);
    if(id_nx != -1){
      buffer.Nxyz.push_back(glm::vec3(row[id_nx], row[id_nx+1], row[id_nx+2]));
    }

    //Color
    int id_rgb = get_property_id(config, io::imp::RGB);
    if(id_rgb != -1){
      buffer.rgb.push_back(glm::vec3(row[id_nx], row[id_nx+1], row[id_nx+2]));
    }

    //Intensity
    int id_i = get_property_id(config, io::imp::I);
    if(id_i != -1){
      buffer.Is.push_back(row[id_i]);
    }
  }

  //---------------------------
}
void Ascii::parse_face(io::imp::Configuration* config, std::ifstream& file){
  if(config->nb_face == 0) return;
  //---------------------------

  //Init
  io::imp::Buffer buffer_tmp = buffer;
  this->buffer = {};

  //Retrieve face data
  std::string line;
  float nb_vertice;
  while(std::getline(file, line)){
    //Data
    std::istringstream iss(line);
    iss >> nb_vertice;
    std::vector<int> idx;
    float d;
    for(int i=0; i<nb_vertice; i++){
      iss >> d;
      idx.push_back(d);
    }

    //Retrieve face data
    for(int i=0; i<nb_vertice; i++){
      //Location
      buffer.xyz.push_back(buffer_tmp.xyz[idx[i]]);

      //Normal
      if(get_property_id(config, io::imp::NXYZ) != -1){
        buffer.Nxyz.push_back(buffer_tmp.Nxyz[idx[i]]);
      }

      //Intensity
      if(get_property_id(config, io::imp::I) != -1){
        buffer.Is.push_back(buffer_tmp.Is[idx[i]]);
      }
    }
  }

  //Deduce drawing type
  if(nb_vertice == 3){
    config->topology = utl::topology::TRIANGLE;
  }
  else if(nb_vertice == 4){
    config->topology = utl::topology::QUAD;
  }

  //---------------------------
}
int Ascii::get_property_id(io::imp::Configuration* config, io::imp::Field field){
  //---------------------------

  for(int i=0; i<config->vec_property.size(); i++){
    io::imp::Property* property = &config->vec_property[i];

    if(property->field == field){
      return i;
    }
  }

  //---------------------------
  return -1;
}

}
