#include "Exporter.h"


namespace format::ply{

//Constructor / Destructor
Exporter::Exporter(){}
Exporter::~Exporter(){}

//Main exporter functions
void Exporter::export(utl::type::Data* data, std::string path){
  string format = "binary_little_endian";
  //---------------------------

  std::ofstream file(path, ios::binary);

  this->Exporter_header(file, format, data);
  this->Exporter_data_binary(file, data);

  file.close();

  //---------------------------
}
void Exporter::export_ascii(utl::type::Data* data, std::string path){
  string format == "ascii";
  //---------------------------

  std::ofstream file(filePath);

  this->Exporter_header(file, format, data);
  this->Exporter_data_ascii(file, data);

  file.close();

  //---------------------------
}

//Subfunction
void Exporter::write_header(std::ofstream& file, std::string format, utl::type::Data* data){
  //---------------------------

  int property_number = 3;
  vector<string> property_name;

  //Write header
  file << "ply" << endl;
  file << "format " + format + " 1.0" << endl;
  file << "element vertex " << data->size << endl;

  file << "property float32 x" << endl;
  file << "property float32 y" << endl;
  file << "property float32 z" << endl;
  property_name.push_back("x");
  property_name.push_back("y");
  property_name.push_back("z");

  if(data->rgb.size() != 0){
    file << "property uchar red" << endl;
    file << "property uchar green" << endl;
    file << "property uchar blue" << endl;

    property_name.push_back("r");
    property_name.push_back("g");
    property_name.push_back("b");
    property_number += 3;
  }
  if(data->Nxyz.size() != 0){
    file << "property float32 nx" << endl;
    file << "property float32 ny" << endl;
    file << "property float32 nz" << endl;

    property_name.push_back("nx");
    property_name.push_back("ny");
    property_name.push_back("nz");
    property_number += 3;
  }
  if(data->Is.size() != 0){
    file << "property float32 scalar_field" << endl;

    property_name.push_back("I");
    property_number++;
  }
  if(data->ts.size() != 0){
    file << "property float32 timestamp" << endl;

    property_name.push_back("ts");
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
      file << setprecision(precision) << Is << " ";
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
      //Location
      if(property_name[j] == "x"){
        for(int k=0; k<3; k++){
          memcpy(block_data + offset, &xyz[i][k], sizeof(float));
          offset += sizeof(float);
        }
      }

      //Color
      if(property_name[j] == "r"){
        for(int k=0; k<3; k++){
          int color_int = rgb[i][k] * 255;
          memcpy(block_data + offset, &color_int, sizeof(u_char));
          offset += sizeof(u_char);
        }
      }

      //Intensity
      if(property_name[j] == "I"){
        memcpy(block_data + offset, &Is[i], sizeof(float));
        offset += sizeof(float);
      }

      //Normal
      if(property_name[j] == "nx"){
        for(int k=0; k<3; k++){
          memcpy(block_data + offset, &Nxyz[i][k], sizeof(float));
          offset += sizeof(float);
        }
      }

      //Timestamp
      if(property_name[j] == "ts"){
        memcpy(block_data + offset, &ts[i], sizeof(float));
        offset += sizeof(float);
      }
    }
  }

  //Read all data blocks & read the last data block
  file.write(block_data, block_size);

  //---------------------------
}

}
