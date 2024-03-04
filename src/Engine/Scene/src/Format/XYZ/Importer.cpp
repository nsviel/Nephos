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
utl::file::Entity* Importer::import(std::string path){
  utl::file::Entity* data = new utl::file::Entity();
  //---------------------------

  data->name = utl::fct::info::get_name_from_path(path);
  data->path.data = path;

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
