#include "Importer.h"


namespace fmt::xyz{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->format.ascii = ".xyz";

  //---------------------------
}
Importer::~Importer(){}

//Main function
std::shared_ptr<utl::base::Element> Importer::import(utl::base::Path path){
  /*utl::base::Data& data = new utl::base::Data();
  //---------------------------

  data.name = utl::path::get_name_from_path(path.data);
  data.path = path;

  //Open file
  std::ifstream infile(path.data);

  //Retrieve data
  std::string line;
  float a, b, c, d, e, f;
  while(std::getline(infile, line)){
    std::istringstream iss(line);
    iss >> a >> b >> c >> d >> e >> f;

    //Data extraction
    data.xyz.push_back(glm::vec3(a, b, c));
    data.rgb.push_back(glm::vec4(d, e, f, 1));
  }
*/
  //---------------------------
  return nullptr;
}

}
