#include "GLTF_importer.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION



//Constructor / Destructor
GLTF_importer::GLTF_importer(){
  //---------------------------

  //---------------------------
}
GLTF_importer::~GLTF_importer(){}

//Main load functions
utl::media::File* GLTF_importer::Loader(std::string path){
  utl::media::File* data = new utl::media::File();
  //---------------------------

  data->name = info::get_name_from_path(path);
  data->path_data = path;

  this->load_file(path);

  //---------------------------
  return data;
}

//Subfunction
void GLTF_importer::load_file(std::string path){
  //---------------------------

  tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;

  bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);
  //bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, argv[1]); // for binary glTF(.glb)
  if (!warn.empty()) {
    printf("Warn: %s\n", warn.c_str());
  }
  if (!err.empty()) {
    printf("Err: %s\n", err.c_str());
  }
  if (!ret) {
    printf("Failed to parse glTF\n");
  }

  //---------------------------
}
