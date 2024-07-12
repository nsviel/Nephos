#include "Binary.h"

#include <Data/Namespace.h>


namespace fmt::ply::importer{

//Constructor / Destructor
Binary::Binary(){
  //---------------------------

  //---------------------------
}
Binary::~Binary(){}

//Main function
void Binary::parse_binary(dat::base::Object* object, fmt::ply::Header* header){
  this->header = header;
  //---------------------------

  //Open file
  std::ifstream file(header->path, std::ios::binary);
  this->pass_header(file);

  //Read data
  switch(header->encoding){
    case BINARY_LITTLE_ENDIAN:{
      this->parse_vertex_little_endian(file);
      this->parse_face_little_endian(file);
      break;
    }
    case BINARY_BIG_ENDIAN:{
      this->parse_vertex_big_endian(file);
      this->parse_face_big_endian(file);
      break;
    }
  }

  //Store result
  object->data.xyz = data.xyz;
  object->data.Nxyz = data.Nxyz;
  object->data.Is = data.Is;
  object->data.size = data.xyz.size();

  //Close file
  file.close();

  //---------------------------
}

//Parser
void Binary::parse_vertex_little_endian(std::ifstream& file){
  this->data = {};
  //---------------------------

  //Read data
  int block_size = header->vec_property.size() * header->nb_vertex * sizeof(float);
  char* block_data = new char[block_size];
  file.read(block_data, block_size);

  //Convert raw data into decimal data
  int offset = 0;
  std::vector<std::vector<float>> block_vec;
  block_vec.resize(header->vec_property.size(), std::vector<float>(header->nb_vertex));
  for(int i=0; i<header->nb_vertex; i++){
    for(int j=0; j<header->vec_property.size(); j++){
      fmt::ply::Property* property = &header->vec_property[j];

      switch(property->type){
        case fmt::ply::FLOAT32:{
          float value = get_float_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case fmt::ply::FLOAT64:{
          float value = get_double_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case fmt::ply::UINT8:{
          float value = get_uint8_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case fmt::ply::UINT16:{
          float value = get_uint16_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case fmt::ply::UINT32:{
          float value = get_uint32_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case fmt::ply::UCHAR:{
          float value = get_uchar_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case fmt::ply::USHORT:{
          float value = get_ushort_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
      }

    }
  }

  //Resize std::vectors accordingly
  data.xyz.resize(header->nb_vertex, glm::vec3(0,0,0));
  if(get_property_id(fmt::ply::TS) != -1) data.ts.resize(header->nb_vertex, 0);
  if(get_property_id(fmt::ply::I) != -1) data.Is.resize(header->nb_vertex, 0);
  if(get_property_id(fmt::ply::NX) != -1) data.Nxyz.resize(header->nb_vertex, glm::vec3(0,0,0));
  if(get_property_id(fmt::ply::R) != -1) data.rgb.resize(header->nb_vertex, glm::vec4(0,0,0,0));

  //Insert data in the adequate std::vector
  //#pragma omp parallel for
  for(int i=0; i<header->nb_vertex; i++){
    for(int j=0; j<header->vec_property.size(); j++){
      fmt::ply::Property* property = &header->vec_property[j];

      switch(property->field){
        case fmt::ply::X:{ //Location
          glm::vec3 point = glm::vec3(block_vec[j][i], block_vec[j+1][i], block_vec[j+2][i]);
          data.xyz[i] = point;
          break;
        }
        case fmt::ply::NX:{ //Normal
          glm::vec3 normal = glm::vec3(block_vec[j][i], block_vec[j+1][i], block_vec[j+2][i]);
          data.Nxyz[i] = normal;
          break;
        }
        case fmt::ply::R:{ //Color
          float red = block_vec[j][i] / 255;
          float green = block_vec[j+1][i] / 255;
          float blue = block_vec[j+2][i] / 255;
          glm::vec4 rgb = glm::vec4(red, green, blue, 1.0f);
          data.rgb[i] = rgb;
          break;
        }
        case fmt::ply::I:{ //Intensity
          float Is = block_vec[j][i];
          data.Is[i] = Is;
          break;
        }
        case fmt::ply::TS:{ //Timestamp
          float ts = block_vec[j][i];
          data.ts[i] = ts;
          break;
        }
      }

    }
  }

  //---------------------------
}
void Binary::parse_face_little_endian(std::ifstream& file){
  if(header->nb_face == 0) return;
  //---------------------------

  //Init
  utl::base::Data data_tmp = data;
  this->data = {};

  //Get face index
  int block_size_id = 4 * header->nb_face * sizeof(int);
  char* block_data_id = new char[block_size_id];
  file.read(block_data_id, block_size_id);

  //Convert raw data into decimal data
  int offset = 0;
  int nb_vertice;
  for(int i=0; i<header->nb_face; i++){
    //Get number of face vertices
    int value =  (int)*((unsigned char *) (block_data_id + offset));
    offset += sizeof(unsigned char);
    nb_vertice = value;

    //Get face vertices index
    std::vector<int> idx;
    for(int j=0; j<value; j++){
      int value =  *((int *) (block_data_id + offset));
      offset += sizeof(int);
      idx.push_back(value);
    }

    //Location
    for(int j=0; j<idx.size(); j++){
      int& index = idx[j];

      if(index < data_tmp.xyz.size()){
        data.xyz.push_back(data_tmp.xyz[index]);
      }
    }
  }

  //Deduce drawing type
  if(nb_vertice == 3){
    header->topology = utl::topology::TRIANGLE;
  }
  else if(nb_vertice == 4){
    header->topology = utl::topology::QUAD;
  }

  //---------------------------
}
void Binary::parse_vertex_big_endian(std::ifstream& file){
  this->data = {};
  //---------------------------

  //Read data
  int block_size = header->vec_property.size() * header->nb_vertex * sizeof(float);
  char* block_data = new char[block_size];
  file.read(block_data, block_size);

  //Convert raw data into decimal data
  int offset = 0;
  std::vector<std::vector<float>> block_vec;
  block_vec.resize(header->vec_property.size(), std::vector<float>(header->nb_vertex));
  for(int i=0; i<header->nb_vertex; i++){
    for(int j=0; j<header->vec_property.size(); j++){
      float value = get_float_from_binary(block_data, offset);
      block_vec[j][i] = reverse_float(value);
    }
  }

  //Resize std::vectors accordingly
  data.xyz.resize(header->nb_vertex, glm::vec3(0,0,0));
  if(get_property_id(fmt::ply::TS) != -1) data.ts.resize(header->nb_vertex, 0);
  if(get_property_id(fmt::ply::I) != -1) data.Is.resize(header->nb_vertex, 0);

  //Insert data in the adequate std::vector
  #pragma omp parallel for
  for(int i=0; i<header->nb_vertex; i++){
    for(int j=0; j<header->vec_property.size(); j++){
      fmt::ply::Property* property = &header->vec_property[j];

      switch(property->field){
        case fmt::ply::X:{ //Location
          glm::vec3 point = glm::vec3(block_vec[j][i], block_vec[j+1][i], block_vec[j+2][i]);
          data.xyz[i] = point;
          break;
        }
        case fmt::ply::I:{ //Intensity
          float Is = block_vec[j][i];
          data.Is[i] = Is;
          break;
        }
        case fmt::ply::TS:{ //Timestamp
          float ts = block_vec[j][i];
          data.ts[i] = ts;
          break;
        }
      }

    }
  }

  //---------------------------
}
void Binary::parse_face_big_endian(std::ifstream& file){
  if(header->nb_face == 0) return;
  //---------------------------

  //Init
  utl::base::Data data_tmp = data;
  this->data = {};

  //Get face index
  int block_size_id = 4 * header->nb_face * sizeof(int);
  char* block_data_id = new char[block_size_id];
  file.read(block_data_id, block_size_id);

  //Convert raw data into decimal data
  int offset = 0;
  int nb_vertice;
  for(int i=0; i<header->nb_face; i++){
    //Get number of face vertices
    int value =  (int)*((unsigned char *) (block_data_id + offset));
    offset += sizeof(unsigned char);
    nb_vertice = value;

    //Get face vertices index
    std::vector<int> idx;
    for(int j=0; j<value; j++){
      int value =  *((int *) (block_data_id + offset));
      offset += sizeof(int);
      idx.push_back(reverse_int(value));
    }

    //Location
    for(int j=0; j<idx.size(); j++){
      data.xyz.push_back(data_tmp.xyz[idx[j]]);
    }
  }

  //Deduce drawing type
  if(nb_vertice == 3){
    header->topology = utl::topology::TRIANGLE;
  }
  else if(nb_vertice == 4){
    header->topology = utl::topology::QUAD;
  }

  //---------------------------
}

//Subfunction
void Binary::pass_header(std::ifstream& file){
  std::string line;
  //---------------------------

  while(std::getline(file, line)){
    if(line == "end_header"){
      break;
    }
  }

  //---------------------------
}
float Binary::reverse_float(const float inFloat){
   float retVal;
   char *floatToConvert = ( char* ) & inFloat;
   char *returnFloat = ( char* ) & retVal;

   // swap the bytes into a temporary buffer
   returnFloat[0] = floatToConvert[3];
   returnFloat[1] = floatToConvert[2];
   returnFloat[2] = floatToConvert[1];
   returnFloat[3] = floatToConvert[0];

   return retVal;
}
int Binary::reverse_int(const int inInt){
   int retVal;
   char *intToConvert = ( char* ) & inInt;
   char *returnInt = ( char* ) & retVal;

   // swap the bytes into a temporary buffer
   returnInt[0] = intToConvert[3];
   returnInt[1] = intToConvert[2];
   returnInt[2] = intToConvert[1];
   returnInt[3] = intToConvert[0];

   return retVal;
}
void Binary::reorder_by_timestamp(utl::base::Data* data){/*
  std::vector<glm::vec3> pos;
  std::vector<float> ts;
  std::vector<float> Is;
  //---------------------------

  if(data.ts.size() != 0){
    //Check fornon void and reorder by index
    for(auto i: math::sort_by_index(data.ts)){
      if(data.xyz[i] != glm::vec3(0, 0, 0)){
        //Location adn timestamp
        ts.push_back(data.ts[i]);
        pos.push_back(data.xyz[i]);

        //Intensity
        if(data.Is.size() != 0){
          Is.push_back(data.Is[i]);
        }
      }
    }

    //Set new std::vectors
    data.xyz = pos;
    data.ts = ts;
    data.Is = Is;
  }
*/
  //---------------------------
}
int Binary::get_property_id(fmt::ply::Field field){
  //---------------------------

  for(int i=0; i<header->vec_property.size(); i++){
    fmt::ply::Property* property = &header->vec_property[i];

    if(property->field == field){
      return i;
    }
  }

  //---------------------------
  return -1;
}

//Binary type
float Binary::get_float_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<float*>(block_data + offset));
  offset += sizeof(float);

  //---------------------------
  return value;
}
float Binary::get_double_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<double*>(block_data + offset));
  offset += sizeof(double);

  //---------------------------
  return value;
}
float Binary::get_int_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<int*>(block_data + offset));
  offset += sizeof(int);

  //---------------------------
  return value;
}
float Binary::get_uint8_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<uint8_t*>(block_data + offset));
  offset += sizeof(uint8_t);

  //---------------------------
  return value;
}
float Binary::get_uint16_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<uint16_t*>(block_data + offset));
  offset += sizeof(uint16_t);

  //---------------------------
  return value;
}
float Binary::get_uint32_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<uint32_t*>(block_data + offset));
  offset += sizeof(uint32_t);

  //---------------------------
  return value;
}
float Binary::get_uchar_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<unsigned char*>(block_data + offset));
  offset += sizeof(unsigned char);

  //---------------------------
  return value;
}
float Binary::get_ushort_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<unsigned short*>(block_data + offset));
  offset += sizeof(unsigned short);

  //---------------------------
  return value;
}

}
