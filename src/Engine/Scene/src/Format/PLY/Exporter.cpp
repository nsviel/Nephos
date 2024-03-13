#include "Exporter.h"


namespace format::ply{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->format = "ply";

  //---------------------------
}
Exporter::~Exporter(){}

//Main exporter functions
void Exporter::export_ascii(utl::type::Data* data, std::string path){
  string format = "ascii";
  //---------------------------

  std::ofstream file(path);

  this->write_header(file, format, data);
  this->write_data_ascii(file, data);

  file.close();

  //---------------------------
}
void Exporter::export_binary(utl::type::Data* data, std::string path){
  string format = "binary_little_endian";
  //---------------------------

  std::ofstream file(path, ios::binary);

  this->write_header(file, format, data);
  this->write_data_binary(file, data);

  file.close();

  //---------------------------
}

//Subfunction
void Exporter::write_header(std::ofstream& file, std::string format, utl::type::Data* data){
  //---------------------------

  this->vec_property.clear();

  //Write header
  file << "ply" << endl;
  file << "format " + format + " 1.0" << endl;
  file << "element vertex " << data->size << endl;

  file << "property float32 x" << endl;
  file << "property float32 y" << endl;
  file << "property float32 z" << endl;
  vec_property.push_back(format::ply::XYZ);
  vec_property.push_back(format::ply::EMPTY);
  vec_property.push_back(format::ply::EMPTY);
  this->property_number = 3;

  if(data->rgb.size() != 0){
    file << "property uchar red" << endl;
    file << "property uchar green" << endl;
    file << "property uchar blue" << endl;

    vec_property.push_back(format::ply::RGB);
    vec_property.push_back(format::ply::EMPTY);
    vec_property.push_back(format::ply::EMPTY);
    this->property_number += 3;
  }
  if(data->Nxyz.size() != 0){
    file << "property float32 nx" << endl;
    file << "property float32 ny" << endl;
    file << "property float32 nz" << endl;

    vec_property.push_back(format::ply::N);
    vec_property.push_back(format::ply::EMPTY);
    vec_property.push_back(format::ply::EMPTY);
    this->property_number += 3;
  }
  if(data->Is.size() != 0){
    file << "property float32 scalar_field" << endl;

    vec_property.push_back(format::ply::I);
    property_number++;
  }
  if(data->ts.size() != 0){
    file << "property float32 timestamp" << endl;

    vec_property.push_back(format::ply::TS);
    property_number++;
  }
  file << "end_header" <<endl;

  //---------------------------
}
void Exporter::write_data_ascii(std::ofstream& file, utl::type::Data* data){
  //---------------------------

  vector<vec3>& xyz = data->xyz;
  vector<vec4>& rgb = data->rgb;
  vector<vec3>& Nxyz = data->Nxyz;
  vector<float>& Is = data->Is;
  int precision = 6;

  //Write data in the file
  for(int i=0; i<xyz.size(); i++){
    file << fixed;

    //Location
    file << setprecision(precision) << xyz[i].x <<" "<< xyz[i].y <<" "<< xyz[i].z <<" ";

    //Color
    if(rgb.size() != 0){
      file << setprecision(0) << rgb[i].x * 255 <<" "<< rgb[i].y * 255 <<" "<< rgb[i].z * 255 <<" ";
    }

    //Normal
    if(Nxyz.size() != 0){
      file << setprecision(precision) << Nxyz[i].x <<" "<< Nxyz[i].y <<" "<< Nxyz[i].z <<" ";
    }

    //Intensity
    if(Is.size() != 0){
      file << setprecision(precision) << Is[i] << " ";
    }

    file << endl;
  }

  //---------------------------
}
void Exporter::write_data_binary(std::ofstream& file, utl::type::Data* data){
  //---------------------------

  vector<vec3>& xyz = data->xyz;
  vector<vec4>& rgb = data->rgb;
  vector<vec3>& Nxyz = data->Nxyz;
  vector<float>& Is = data->Is;
  vector<float>& ts = data->ts;
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
        case format::ply::XYZ:{
          memcpy(block_data + offset, &xyz[i], sizeof(vec3));
          offset += sizeof(vec3);
          break;
        }

        //Color
        case format::ply::RGB:{
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
        case format::ply::N:{
          memcpy(block_data + offset, &Nxyz[i], sizeof(vec3));
          offset += sizeof(vec3);
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
