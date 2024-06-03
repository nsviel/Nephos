#include "Importer.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Importer::Importer(ldr::Node* node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->node_engine = node_loader->get_node_engine();
  this->dat_entity = node_data->get_dat_entity();
  this->dat_graph = node_data->get_dat_graph();
  this->dat_set = node_data->get_dat_set();
  this->dat_glyph = node_data->get_dat_glyph();

  this->insert_importer(new format::ply::Importer());
  this->insert_importer(new format::obj::Importer());
  this->insert_importer(new format::csv::Importer());
  this->insert_importer(new format::pts::Importer());
  this->insert_importer(new format::ptx::Importer());
  this->insert_importer(new format::xyz::Importer());

  //---------------------------
}
Importer::~Importer(){}

//Main functions
utl::base::Data* Importer::load_data(std::string path){
  if(!check_file_path(path)) return nullptr;
  //---------------------------

  //Init
  utl::media::Path utl_path;
  utl_path.data = path;

  //Load data from path
  utl::base::Element* element = this->import_from_path(utl_path);
  if(element == nullptr) return nullptr;

  //Convert into data
  utl::base::Data* data = nullptr;
  if(element->type == utl::element::DATA){
    data = dynamic_cast<utl::base::Data*>(element);
  }else if(element->type == utl::element::ENTITY){
    dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
    data = &entity->data;
  }

  //---------------------------
  return data;
}
dat::base::Set* Importer::load_set(utl::media::Path path){
  if(!check_file_path(path.data)) return nullptr;
  //---------------------------

  //Load data from path
  utl::base::Element* element = this->import_from_path(path);
  if(element == nullptr) return nullptr;

  //Convert into set
  dat::base::Set* set = nullptr;
  if(element->type == utl::element::SET){
    set = dynamic_cast<dat::base::Set*>(element);
  }

  //Insert loaded set into graph
  if(set != nullptr){
    dat::base::Set* set_graph = dat_graph->get_set_graph();
    dat_set->add_subset(set_graph, set);
    set->is_locked = true;
  }

  //---------------------------
  return set;
}
dat::base::Object* Importer::load_object(utl::media::Path path){
  if(!check_file_path(path.data)) return nullptr;
  //---------------------------

  //Load data from path
  utl::base::Element* element = this->import_from_path(path);
  if(element == nullptr) return nullptr;

  //Convert into object
  dat::base::Object* object = nullptr;
  if(element->type == utl::element::ENTITY){
    object = dynamic_cast<dat::base::Object*>(element);
  }

  //Insert loaded entity into graph
  if(object != nullptr){
    dat::base::Set* set_graph = dat_graph->get_set_graph();
    dat_set->insert_entity(set_graph, object);
  }

  //---------------------------
  return object;
}

//Subfunction
bool Importer::check_file_path(std::string path){
  //---------------------------

  //Check file existence
  if(utl::file::is_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return false;
  }

  //Check file format
  std::string format = utl::path::get_format_from_path(path);
  if(!this->is_format_supported(format)){
    cout<<"[error] '"<<format<<"' file format not supported"<<endl;
    cout<<"Supported file formats:"<<endl;
    for(int i=0; i<vec_importer.size(); i++){
      ldr::base::Importer* importer = vec_importer[i];
      cout<<"o "<<importer->format<<endl;
    }
    return false;
  }

  //---------------------------
  return true;
}
dat::base::Object* Importer::create_object(utl::file::Data* data){
  //---------------------------

  dat::base::Object* object = new dat::base::Object();
  object->name = data->name;
  object->data = *create_data(data);

  dat_entity->init_entity(object);
  dat_glyph->insert_glyph(object);

  //---------------------------
  return object;
}
utl::base::Data* Importer::create_data(utl::file::Data* file){
  //---------------------------

  utl::base::Data* data = new utl::base::Data();
  data->name = file->name;
  data->path = file->path.data;
  data->format = utl::path::get_format_from_path(file->path.data);
  data->size = file->xyz.size();
  data->topology.type = file->draw_type;

  data->xyz = file->xyz;
  data->rgb = file->rgb;
  data->uv = file->uv;

  //If no color, fill it with white
  if(data->rgb.size() == 0){
    for(int i=0; i<file->xyz.size(); i++){
      data->rgba.push_back(vec4(1, 1, 1, 1));
    }
  }else{
    for(int i=0; i<file->rgb.size(); i++){
      glm::vec3& rgb = file->rgb[i];
      data->rgba.push_back(vec4(rgb.x, rgb.y, rgb.z, 1));
    }
  }

  //---------------------------
  return data;
}

//Import function
utl::base::Element* Importer::import_from_path(utl::media::Path path){
  utl::base::Element* element = nullptr;
  //---------------------------

  std::string format = utl::path::get_format_from_path(path.data);

  for(int i=0; i<vec_importer.size(); i++){
    ldr::base::Importer* importer = vec_importer[i];

    if(importer->format == format){
      //Check for discrete gpu requirement
      /*if(importer->require_discrete_gpu && vk_interface->is_gpu_discrete() == false){
        cout<<"[error] no discrete GPU - could not load " + importer->format + " file"<<endl;
        continue;
      }*/

      element = importer->import(path);
    }
  }

  //---------------------------
  return element;
}
void Importer::insert_importer(ldr::base::Importer* importer){
  //---------------------------

  this->vec_importer.push_back(importer);

  //---------------------------
}
bool Importer::is_format_supported(std::string format){
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    ldr::base::Importer* importer = vec_importer[i];

    if(format == importer->format){
      return true;
    }
  }

  //---------------------------
  return false;
}
std::vector<std::string> Importer::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    ldr::base::Importer* importer = vec_importer[i];
    vec_format.push_back(importer->format);
  }

  //---------------------------
  return vec_format;
}

}
