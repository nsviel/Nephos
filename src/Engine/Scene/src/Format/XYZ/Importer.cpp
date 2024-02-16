#include "Importer.h"


namespace format::xyz{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->format = "xyz";

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::media::File* Importer::import(std::string path){
  utl::media::File* data = new utl::media::File();
  //---------------------------

  data->name = utl::fct::info::get_name_from_path(path);
  data->path_data = path;

  //Open file
  std::ifstream infile(path);

  //Retrieve data
  std::string line;
  float a, b, c, d, e, f;
  while (std::getline(infile, line)){
    std::istringstream iss(line);
    iss >> a >> b >> c >> d >> e >> f;

    //Data extraction
    data->xyz.push_back(glm::vec3(a, b, c));
    data->rgb.push_back(glm::vec4(d, e, f, 1));
  }

  //---------------------------
  return data;
}

}
