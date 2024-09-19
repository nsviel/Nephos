#include "Loader.h"

#include <IO/Importer/Namespace.h>
#include <IO/Format/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp{

//Constructor / Destructor
Loader::Loader(io::imp::Node* node_importer){
  //---------------------------

  this->io_importer = node_importer->get_io_importer();
  this->io_operation = node_importer->get_io_operation();

  //---------------------------
}
Loader::~Loader(){}

//Main function
std::shared_ptr<utl::base::Data> Loader::load_data(std::string path){
  utl::base::Path utl_path(path);
  if(!check_path(path)) return nullptr;
  //---------------------------

  //Get element
  auto element = import_from_path(utl_path);
  if(!element || element->type != "entity") return nullptr;

  //Convert into entity
  auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element);
  if(!entity) return nullptr;

  //---------------------------
  return entity->data;
}
void Loader::load_set(utl::base::Path path){
  if(!check_path(path)) return;
  //---------------------------

  //Get element
  auto element = import_from_path(path);
  if(!element || element->type != "set") return;

  //Convert into set
  auto set = std::dynamic_pointer_cast<dat::base::Set>(element);
  if(!set) return;

  //Insert it
  io_operation->insert_set(set);

  //---------------------------
}
void Loader::load_directory(utl::base::Path path){
  //---------------------------

  //Get vector of all directory files
  std::vector<std::string> vec_file = utl::path::list_all_file(path.directory);

  //Load object one by one
  for(int i=0; i<vec_file.size(); i++){
    utl::base::Path utl_path(vec_file[i]);
    utl_path.directory = path.directory;

    this->load_object(utl_path);
  }

  //---------------------------
}
void Loader::load_object(utl::base::Path path){
  if(!check_path(path)) return;
  //---------------------------

  //Get element
  auto element = import_from_path(path);
  if(!element || element->type != "entity") return;

  //Convert into object
  auto object = std::dynamic_pointer_cast<dat::base::Object>(element);
  if(!object) return;

  //Insert it
  io_operation->insert_object(object);

  //---------------------------
}
void Loader::load_object(utl::base::Path path, utl::base::Path path_transfo){
  if(!check_path(path)) return;
  //---------------------------

  //Get element
  auto element = import_from_path(path);
  if(!element || element->type != "entity") return;

  //Convert into object
  auto object = std::dynamic_pointer_cast<dat::base::Object>(element);
  if(!object) return;
  object->pose->path = path_transfo;

  //Insert it
  io_operation->insert_object(object);

  //---------------------------
}
void Loader::load_object_textured(utl::base::Path path, utl::base::Path path_texture){
  if(!check_path(path)) return;
  //---------------------------

  //Get element
  auto element = import_from_path(path);
  if(!element || element->type != "entity") return;

  //Convert into object
  auto object = std::dynamic_pointer_cast<dat::base::Object>(element);
  if(!object) return;

  //Texture
  std::shared_ptr<utl::media::Image> texture = std::make_shared<utl::media::Image>();
  dat::img::load_image_data(*texture, path_texture.build());
  texture->name = "texture";
  object->data->map_texture[texture->name] = texture;

  //Insert it
  io_operation->insert_object(object);

  //---------------------------
}

//Subfunction
bool Loader::check_path(utl::base::Path utl_path){
  //---------------------------

  //Check file existence
  std::string path = utl_path.build();
  if(utl::file::is_exist(path) == false){
    std::cout<<"[error] File doesn't exists at "<<path<<std::endl;
    return false;
  }

  //Check file format
  if(!io_importer->is_format_supported(utl_path.format)){
    std::cout<<"[error] '"<<utl_path.format<<" format not supported"<<std::endl;
    return false;
  }

  //---------------------------
  return true;
}
std::shared_ptr<utl::base::Element> Loader::import_from_path(utl::base::Path path){
  //---------------------------

  //Obtain corresponding importer
  io::base::Importer* importer = io_importer->obtain_importer(path.format);
  if(importer == nullptr) return nullptr;

  //Import element from it
  std::shared_ptr<utl::base::Element> element = importer->import(path);

  //---------------------------
  return element;
}

}
