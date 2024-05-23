#include "Importer.h"


namespace format::ply{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->format = "ply";

  //---------------------------
}
Importer::~Importer(){}

//Main loader functions
utl::media::File* Importer::import(utl::media::Path path){
  //---------------------------

  utl::file::Data* entity = new utl::file::Data();
  entity->name = utl::path::get_name_from_path(path.data);
  entity->path = path;
  entity->draw_type = utl::topology::POINT;
  this->face_number = 0;

  //Get format type
  std::ifstream file(path.data);
  this->parse_header(file);

  //Open data
  switch(file_format){
    case ASCII:{
      //Open file
      std::ifstream file(path.data);

      //Read header
      this->parse_header(file);

      //Read data
      if(face_number == 0){
        this->parse_ascii(file, entity);
      }else{
        this->parse_ascii_withface(file, entity);
      }

      file.close();

      break;
    }
    case BINARY_LITTLE_ENDIAN:{
      //Open file
      std::ifstream file(path.data, std::ios::binary);

      //Read header
      this->parse_header(file);

      //Read data
      if(face_number == 0){
        this->parse_bin_little_endian(file, entity);
      }else{
        this->parse_bin_little_endian_withface(file, entity);
      }

      //Close file
      file.close();
      break;
    }
    case BINARY_BIG_ENDIAN:{
      //Open file
      std::ifstream file(path.data, std::ios::binary);

      //Read header
      this->parse_header(file);

      //Read data
      if(face_number == 0){
        this->parse_bin_big_endian(file, entity);
      }else{
        this->parse_bin_big_endian_withface(file, entity);
      }

      //Close file
      file.close();
      break;
    }
  }

  //---------------------------
  return entity;
}

//Header
void Importer::parse_header(std::ifstream& file){
  this->vec_property.clear();
  //---------------------------

  // Separate the header
  std::string line, h1, h2, h3, h4;
  bool vertex_ended = false;
  do{
    getline(file, line);
    std::istringstream iss(line);
    iss >> h1 >> h2 >> h3 >> h4;

    //Retrieve format
    if(h1 == "format"){
      this->parse_header_format(h2);
    }

    //Retrieve number of point
    if(h1 + h2 == "elementvertex"){
      this->point_number = std::stoi(h3);
    }

    //Retrieve property
    if(h1 == "property" && vertex_ended == false){
      this->parse_header_property(h2, h3);
    }

    //Retrieve property
    if(h1 + h2 == "elementface"){
      vertex_ended = true;
      this->face_number = std::stoi(h3);
    }
  } while(line.find("end_header") != 0);

  //---------------------------
}
void Importer::parse_header_format(std::string format){
  //---------------------------

  if(format == "ascii") this->file_format = ASCII;
  else if(format == "binary_little_endian") this->file_format = BINARY_LITTLE_ENDIAN;
  else if(format == "binary_big_endian") this->file_format = BINARY_BIG_ENDIAN;
  else{
    cout<<"[warning] Unknown format: "<<format<<endl;
    return;
  }

  //---------------------------
}
void Importer::parse_header_property(std::string type, std::string field){
  format::ply::Property property;
  //---------------------------

  //Property type
  if(type == "float" || type == "float32") property.type = format::ply::FLOAT32;
  else if(type == "float64" || type == "double") property.type = format::ply::FLOAT64;
  else if(type == "uint" || type == "uint8") property.type = format::ply::UINT8;
  else if(type == "uint16") property.type = format::ply::UINT16;
  else if(type == "int" || type == "int32") property.type = format::ply::UINT32;
  else if(type == "uchar") property.type = format::ply::UCHAR;
  else if(type == "ushort") property.type = format::ply::USHORT;
  else{
    cout<<"[warning] Unknown property type: "<<type<<endl;
    return;
  }

  //Property field
  if(field == "x") property.field = format::ply::X;
  else if(field == "y") property.field = format::ply::Y;
  else if(field == "z") property.field = format::ply::Z;
  else if(field == "timestamp") property.field = format::ply::TS;
  else if(field == "nx") property.field = format::ply::NX;
  else if(field == "ny") property.field = format::ply::NY;
  else if(field == "nz") property.field = format::ply::NZ;
  else if(field == "red") property.field = format::ply::R;
  else if(field == "green") property.field = format::ply::G;
  else if(field == "blue") property.field = format::ply::B;
  else if(field == "scalar_field" || field == "scalar_Scalar_field" || field == "intensity") property.field = format::ply::I;
  else{
    //cout<<"[warning] Unknown property field: "<<field<<endl;
    property.field = format::ply::VOID;
  }

  //Store property
  vec_property.push_back(property);

  //---------------------------
}

//ASCII
void Importer::parse_ascii(std::ifstream& file, utl::file::Data* entity){
  std::vector<glm::vec3> vertex;
  std::vector<glm::vec3> normal;
  std::vector<float> intensity;
  //---------------------------

  //Retrieve vertex data
  std::string line;
  int cpt = 0;
  while (std::getline(file, line)){
    //Check vertex number
    if(cpt == point_number){
      break;
    }
    cpt++;

    //Stocke all line values
    std::istringstream iss(line);
    std::vector<float> data;
    for(int i=0; i<vec_property.size(); i++){
      float d;
      iss >> d;
      data.push_back(d);
    }

    //Location
    int id_x = get_property_id(format::ply::X);
    if(id_x != -1){
      vertex.push_back(glm::vec3(data[id_x], data[id_x+1], data[id_x+2]));
    }

    //Normal
    int id_nx = get_property_id(format::ply::NX);
    if(id_nx != -1){
      normal.push_back(glm::vec3(data[id_nx], data[id_nx+1], data[id_nx+2]));
    }

    //Intensity
    int id_i = get_property_id(format::ply::I);
    if(id_i != -1){
      intensity.push_back(data[id_i]);
    }
  }

  entity->xyz = vertex;
  entity->Nxyz = normal;
  entity->Is = intensity;

  //---------------------------
  entity->nb_element = entity->xyz.size();
}
void Importer::parse_ascii_withface(std::ifstream& file, utl::file::Data* entity){
  std::vector<glm::vec3> vertex;
  std::vector<glm::vec3> normal;
  std::vector<float> intensity;
  //---------------------------

  //Retrieve vertex data
  std::string line;
  for(int i=0; i<point_number; i++){
    //Get line
    std::getline(file, line);
    std::istringstream iss(line);

    //Stocke all line values
    std::vector<float> data;
    float d;
    for(int i=0; i<vec_property.size(); i++){
      iss >> d;
      data.push_back(d);
    }

    //Location
    int id_x = get_property_id(format::ply::X);
    if(id_x != -1){
      vertex.push_back(glm::vec3(data[id_x], data[id_x+1], data[id_x+2]));
    }

    //Normal
    int id_nx = get_property_id(format::ply::NX);
    if(id_nx != -1){
      normal.push_back(glm::vec3(data[id_nx], data[id_nx+1], data[id_nx+2]));
    }

    //Intensity
    int id_i = get_property_id(format::ply::I);
    if(id_i != -1){
      intensity.push_back(data[id_i]);
    }
  }

  //Retrieve face data
  while (std::getline(file, line)){
    std::istringstream iss(line);
    float nb_vertice;
    iss >> nb_vertice;

    //Stocke all line index
    std::vector<int> idx;
    float d;
    for(int i=0; i<nb_vertice; i++){
      iss >> d;
      idx.push_back(d);
    }

    //Retrieve face data
    for(int i=0; i<nb_vertice; i++){
      entity->xyz.push_back(vertex[idx[i]]);
      if(get_property_id(format::ply::NX) != -1){
        entity->Nxyz.push_back(normal[idx[i]]);
      }
      if(get_property_id(format::ply::I) != -1){
        entity->Is.push_back(intensity[idx[i]]);
      }
    }

    //Deduce drawing type
    if(nb_vertice == 3){
      entity->draw_type = utl::topology::TRIANGLE;
    }
    else if(nb_vertice == 4){
      entity->draw_type = utl::topology::QUAD;
    }
  }

  //---------------------------
  entity->nb_element = entity->xyz.size();
}

//Binary
void Importer::parse_bin_little_endian(std::ifstream& file, utl::file::Data* entity){
  //---------------------------

  //Read data
  int block_size = vec_property.size() * point_number * sizeof(float);
  char* block_data = new char[block_size];
  file.read(block_data, block_size);

  //Convert raw data into decimal data
  int offset = 0;
  std::vector<std::vector<float>> block_vec;
  block_vec.resize(vec_property.size(), std::vector<float>(point_number));
  for(int i=0; i<point_number; i++){
    for(int j=0; j<vec_property.size(); j++){
      format::ply::Property* property = &vec_property[j];

      switch(property->type){
        case format::ply::FLOAT32:{
          float value = get_float_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case format::ply::FLOAT64:{
          float value = get_double_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case format::ply::UINT8:{
          float value = get_uint8_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case format::ply::UINT16:{
          float value = get_uint16_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case format::ply::UINT32:{
          float value = get_uint32_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case format::ply::UCHAR:{
          float value = get_uchar_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
        case format::ply::USHORT:{
          float value = get_ushort_from_binary(block_data, offset);
          block_vec[j][i] = value;
          break;
        }
      }

    }
  }

  //Resize std::vectors accordingly
  entity->xyz.resize(point_number, glm::vec3(0,0,0));
  if(get_property_id(format::ply::TS) != -1) entity->ts.resize(point_number, 0);
  if(get_property_id(format::ply::I) != -1) entity->Is.resize(point_number, 0);
  if(get_property_id(format::ply::NX) != -1) entity->Nxyz.resize(point_number, glm::vec3(0,0,0));
  if(get_property_id(format::ply::R) != -1) entity->rgb.resize(point_number, glm::vec4(0,0,0,0));
  entity->nb_element = point_number;

  //Insert data in the adequate std::vector
  //#pragma omp parallel for
  for(int i=0; i<point_number; i++){
    for(int j=0; j<vec_property.size(); j++){
      format::ply::Property* property = &vec_property[j];

      switch(property->field){
        case format::ply::X:{ //Location
          glm::vec3 point = glm::vec3(block_vec[j][i], block_vec[j+1][i], block_vec[j+2][i]);
          entity->xyz[i] = point;
          break;
        }
        case format::ply::NX:{ //Normal
          glm::vec3 normal = glm::vec3(block_vec[j][i], block_vec[j+1][i], block_vec[j+2][i]);
          entity->Nxyz[i] = normal;
          break;
        }
        case format::ply::R:{ //Color
          float red = block_vec[j][i] / 255;
          float green = block_vec[j+1][i] / 255;
          float blue = block_vec[j+2][i] / 255;
          glm::vec4 rgb = glm::vec4(red, green, blue, 1.0f);
          entity->rgb[i] = rgb;
          break;
        }
        case format::ply::I:{ //Intensity
          float Is = block_vec[j][i];
          entity->Is[i] = Is;
          break;
        }
        case format::ply::TS:{ //Timestamp
          float ts = block_vec[j][i];
          entity->ts[i] = ts;
          break;
        }
      }

    }
  }

  //---------------------------
}
void Importer::parse_bin_little_endian_withface(std::ifstream& file, utl::file::Data* entity){
  //---------------------------

  //Read data
  int block_size = vec_property.size() * point_number * sizeof(float);
  char* block_data = new char[block_size];
  file.read(block_data, block_size);

  //Convert raw data into decimal data
  int offset = 0;
  std::vector<std::vector<float>> block_vec;
  block_vec.resize(vec_property.size(), std::vector<float>(point_number));
  for(int i=0; i<point_number; i++){
    for(int j=0; j<vec_property.size(); j++){
      float value = get_float_from_binary(block_data, offset);
      block_vec[j][i] = value;
    }
  }

  //Insert data in the adequate std::vector
  std::vector<glm::vec3> vertex;
  std::vector<glm::vec3> normal;
  std::vector<float> intensity;
  std::vector<float> timestamp;
  for(int i=0; i<point_number; i++){
    for(int j=0; j<vec_property.size(); j++){
      format::ply::Property* property = &vec_property[j];

      switch(property->field){
        case format::ply::X:{ //Location
          glm::vec3 point = glm::vec3(block_vec[j][i], block_vec[j+1][i], block_vec[j+2][i]);
          vertex.push_back(point);
          break;
        }
        case format::ply::I:{ //Intensity
          float Is = block_vec[j][i];
          intensity.push_back(Is);
          break;
        }
        case format::ply::TS:{ //Timestamp
          float ts = block_vec[j][i];
          timestamp.push_back(ts);
          break;
        }
      }

    }
  }

  //Get face index
  int block_size_id = 4 * face_number * sizeof(int);
  char* block_data_id = new char[block_size_id];
  file.read(block_data_id, block_size_id);

  //Convert raw data into decimal data
  offset = 0;
  int nb_vertice;
  for(int i=0; i<face_number; i++){
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
      entity->xyz.push_back(vertex[idx[j]]);
    }
  }

  //Deduce drawing type
  if(nb_vertice == 3){
    entity->draw_type = utl::topology::TRIANGLE;
  }
  else if(nb_vertice == 4){
    entity->draw_type = utl::topology::QUAD;
  }

  //---------------------------
  entity->nb_element = entity->xyz.size();
}
void Importer::parse_bin_big_endian(std::ifstream& file, utl::file::Data* entity){
  //---------------------------

  //Read data
  int block_size = vec_property.size() * point_number * sizeof(float);
  char* block_data = new char[block_size];
  file.read(block_data, block_size);

  //Convert raw data into decimal data
  int offset = 0;
  std::vector<std::vector<float>> block_vec;
  block_vec.resize(vec_property.size(), std::vector<float>(point_number));
  for(int i=0; i<point_number; i++){
    for(int j=0; j<vec_property.size(); j++){
      float value = get_float_from_binary(block_data, offset);
      block_vec[j][i] = reverse_float(value);
    }
  }

  //Resize std::vectors accordingly
  entity->xyz.resize(point_number, glm::vec3(0,0,0));
  if(get_property_id(format::ply::TS) != -1) entity->ts.resize(point_number, 0);
  if(get_property_id(format::ply::I) != -1) entity->Is.resize(point_number, 0);
  entity->nb_element = point_number;

  //Insert data in the adequate std::vector
  #pragma omp parallel for
  for(int i=0; i<point_number; i++){
    for(int j=0; j<vec_property.size(); j++){
      format::ply::Property* property = &vec_property[j];

      switch(property->field){
        case format::ply::X:{ //Location
          glm::vec3 point = glm::vec3(block_vec[j][i], block_vec[j+1][i], block_vec[j+2][i]);
          entity->xyz[i] = point;
          break;
        }
        case format::ply::I:{ //Intensity
          float Is = block_vec[j][i];
          entity->Is[i] = Is;
          break;
        }
        case format::ply::TS:{ //Timestamp
          float ts = block_vec[j][i];
          entity->ts[i] = ts;
          break;
        }
      }

    }
  }

  //---------------------------
}
void Importer::parse_bin_big_endian_withface(std::ifstream& file, utl::file::Data* entity){
  //---------------------------

  //Read data
  int block_size = vec_property.size() * point_number * sizeof(float);
  char* block_data = new char[block_size];
  file.read(block_data, block_size);

  //Convert raw data into decimal data
  int offset = 0;
  std::vector<std::vector<float>> block_vec;
  block_vec.resize(vec_property.size(), std::vector<float>(point_number));
  for(int i=0; i<point_number; i++){
    for(int j=0; j<vec_property.size(); j++){
      float value = get_float_from_binary(block_data, offset);
      block_vec[j][i] = reverse_float(value);
    }
  }

  //Insert data in the adequate std::vector
  std::vector<glm::vec3> vertex;
  std::vector<glm::vec3> normal;
  std::vector<float> intensity;
  std::vector<float> timestamp;
  for(int i=0; i<point_number; i++){
    for(int j=0; j<vec_property.size(); j++){
      format::ply::Property* property = &vec_property[j];

      switch(property->field){
        case format::ply::X:{ //Location
          glm::vec3 point = glm::vec3(block_vec[j][i], block_vec[j+1][i], block_vec[j+2][i]);
          vertex.push_back(point);
          break;
        }
        case format::ply::I:{ //Intensity
          float Is = block_vec[j][i];
          intensity.push_back(Is);
          break;
        }
        case format::ply::TS:{ //Timestamp
          float ts = block_vec[j][i];
          timestamp.push_back(ts);
          break;
        }
      }

    }
  }

  //Get face index
  int block_size_id = 4 * face_number * sizeof(int);
  char* block_data_id = new char[block_size_id];
  file.read(block_data_id, block_size_id);

  //Convert raw data into decimal data
  offset = 0;
  int nb_vertice;
  for(int i=0; i<face_number; i++){
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
      entity->xyz.push_back(vertex[idx[j]]);
    }
  }

  //Deduce drawing type
  if(nb_vertice == 3){
    entity->draw_type = utl::topology::TRIANGLE;
  }
  else if(nb_vertice == 4){
    entity->draw_type = utl::topology::QUAD;
  }

  //---------------------------
  entity->nb_element = entity->xyz.size();
}

//Subfunction
float Importer::reverse_float(const float inFloat){
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
int Importer::reverse_int(const int inInt){
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
void Importer::reorder_by_timestamp(utl::file::Data* entity){
  std::vector<glm::vec3> pos;
  std::vector<float> ts;
  std::vector<float> Is;
  //---------------------------

  if(entity->ts.size() != 0){
    //Check fornon void and reorder by index
    for(auto i: math::sort_by_index(entity->ts)){
      if(entity->xyz[i] != glm::vec3(0, 0, 0)){
        //Location adn timestamp
        ts.push_back(entity->ts[i]);
        pos.push_back(entity->xyz[i]);

        //Intensity
        if(entity->Is.size() != 0){
          Is.push_back(entity->Is[i]);
        }
      }
    }

    //Set new std::vectors
    entity->xyz = pos;
    entity->ts = ts;
    entity->Is = Is;
  }

  //---------------------------
}
int Importer::get_property_id(format::ply::Field field){
  //---------------------------

  for(int i=0; i<vec_property.size(); i++){
    format::ply::Property* property = &vec_property[i];

    if(property->field == field){
      return i;
    }
  }

  //---------------------------
  return -1;
}

//Binary type
float Importer::get_float_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<float*>(block_data + offset));
  offset += sizeof(float);

  //---------------------------
  return value;
}
float Importer::get_double_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<double*>(block_data + offset));
  offset += sizeof(double);

  //---------------------------
  return value;
}
float Importer::get_int_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<int*>(block_data + offset));
  offset += sizeof(int);

  //---------------------------
  return value;
}
float Importer::get_uint8_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<uint8_t*>(block_data + offset));
  offset += sizeof(uint8_t);

  //---------------------------
  return value;
}
float Importer::get_uint16_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<uint16_t*>(block_data + offset));
  offset += sizeof(uint16_t);

  //---------------------------
  return value;
}
float Importer::get_uint32_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<uint32_t*>(block_data + offset));
  offset += sizeof(uint32_t);

  //---------------------------
  return value;
}
float Importer::get_uchar_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<unsigned char*>(block_data + offset));
  offset += sizeof(unsigned char);

  //---------------------------
  return value;
}
float Importer::get_ushort_from_binary(char* block_data, int& offset){
  //---------------------------

  float value = static_cast<float>(*reinterpret_cast<unsigned short*>(block_data + offset));
  offset += sizeof(unsigned short);

  //---------------------------
  return value;
}

}
