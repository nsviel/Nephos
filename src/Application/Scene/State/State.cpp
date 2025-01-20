#include "State.h"

#include <Core/Namespace.h>
#include <Scene/Namespace.h>
#include <Utility/Namespace.h>


namespace sce{

//Constructor / Destructor
State::State(sce::Node* node_scene){
  //---------------------------

  //---------------------------
}
State::~State(){}

//Main function
void State::export_json(){
  //---------------------------

  // Create a JSON object to store the matrix values
  nlohmann::json j;
  j["name"] = "first scene"

  // Write the JSON object to the file
  std::ofstream file(path);
  if(file.is_open()){
    file << j.dump(4); // Use dump(4) for pretty printing with an indentation of 4 spaces
    file.close();
  }else{
    std::cerr << "Failed to open the file for writing." << std::endl;
  }

  //---------------------------
}

}
