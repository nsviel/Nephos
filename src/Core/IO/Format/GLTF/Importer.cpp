#include "Importer.h"

#include <Format/GLTF/Mesh.h>
#include <Format/GLTF/Model.h>
#include <Format/GLTF/Structure.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <gltf/tiny_gltf.h>


namespace fmt::gltf{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->gltf_mesh = new fmt::gltf::Mesh();
  this->gltf_model = new fmt::gltf::Model();

  this->format.ascii = ".gltf";
  this->format.binary = ".glb";

  //---------------------------
}
Importer::~Importer(){}

//Main function
std::shared_ptr<utl::base::Element> Importer::import(utl::base::Path path){
  utl::base::Element element;
  //---------------------------

  //Init
  std::shared_ptr<dat::base::Object> object = std::make_shared<dat::base::Object>();
  object->name = utl::path::get_name_from_path(path.build());
  object->data->name = utl::path::get_name_from_path(path.build());
  object->data->path = path;
  object->data->path.format = format.ascii;
  object->data->topology.type = utl::topology::TRIANGLE;

  //Model
  fmt::gltf::Structure tinygltf;
  gltf_model->load_model(tinygltf, path);
  gltf_mesh->parse_meshes(tinygltf, object->data);

  //---------------------------
  return object;
}

//Subfunction

}
