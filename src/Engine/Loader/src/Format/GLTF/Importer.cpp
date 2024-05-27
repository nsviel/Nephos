#include "Importer.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION


namespace format::gltf{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->format = "gltf";

  //---------------------------
}
Importer::~Importer(){}

//Main load functions
utl::media::File* Importer::import(utl::media::Path path){
  utl::file::Data* data = new utl::file::Data();
  //---------------------------

  data->name = utl::path::get_name_from_path(path.data);
  data->path = path;

  this->load_file(path.data);

  //---------------------------
  return data;
}

//Subfunction
void Importer::load_file(std::string path){
  //---------------------------

  tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;

  bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);
  //bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, argv[1]); // for binary glTF(.glb)
  if (!warn.empty()){
    printf("Warn: %s\n", warn.c_str());
  }
  if (!err.empty()){
    printf("Err: %s\n", err.c_str());
  }
  if (!ret){
    printf("Failed to parse glTF\n");
  }

  //---------------------------
}

}
