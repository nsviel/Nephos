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
  this->dat_set = node_data->get_data_set();

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
  dat::base::Set* set = nullptr;
  //---------------------------

  //Init
  if(!check_file_path(path)) return nullptr;
  utl::media::Path utl_path;
  utl_path.data = path;

  //Load data from path
  utl::media::File* file = this->import_from_path(utl_path);
  if(file == nullptr || file->type != utl::file::DATA) return nullptr;
  utl::file::Data* file_data = dynamic_cast<utl::file::Data*>(file);

  utl::base::Data* data = create_data(file_data);

  //Delete raw data
  delete file;

  //---------------------------
  return data;
}
dat::base::Set* Importer::load_set(utl::media::Path file_path){
  //---------------------------

  if(!check_file_path(file_path.data)) return nullptr;

  //Load data from path
  utl::media::File* file = this->import_from_path(file_path);
  if(file == nullptr || file->type != utl::file::DATASET) return nullptr;
  utl::file::Dataset* dataset = dynamic_cast<utl::file::Dataset*>(file);

  //Insert loaded set into scene
  dat::base::Set* set_scene = dat_graph->get_set_graph();
  dat::base::Set* set = dat_set->get_or_create_subset(set_scene, dataset->name);
  set->is_locked = true;

  //Insert all set objects into engine
  for(int i=0; i<dataset->vec_data.size(); i++){
    dat::base::Object* object = create_object(dataset->vec_data[i]);
    dat_set->insert_entity(set, object);
  }

  //Delete raw data
  delete file;

  //---------------------------
  return set;
}
dat::base::Object* Importer::load_object(utl::media::Path file_path){
  //---------------------------

  if(!check_file_path(file_path.data)) return nullptr;

  //Load data from path
  utl::media::File* file = this->import_from_path(file_path);
  if(file == nullptr || file->type != utl::file::DATA) return nullptr;
  utl::file::Data* file_data = dynamic_cast<utl::file::Data*>(file);

  //Data is an entity
  dat::base::Set* set_scene = dat_graph->get_set_graph();
  dat::base::Object* object = create_object(file_data);
  dat_set->insert_entity(set_scene, object);

  //Delete raw data
  delete file;

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

  dat::base::Object* object = new dat::base::Object(node_engine);
  object->name = data->name;
  object->data = *create_data(data);

  dat_entity->init_entity(object);

  //---------------------------
  return object;
}
utl::base::Data* Importer::create_data(utl::file::Data* file){
  //---------------------------

  utl::base::Data* data = new utl::base::Data();
  data->name = file->name;
  data->path = file->path.data;
  data->file_format = utl::path::get_format_from_path(file->path.data);
  data->size = file->xyz.size();
  data->topology.type = file->draw_type;

  data->xyz = file->xyz;
  data->rgb = file->rgb;
  data->uv = file->uv;

  //If no color, fill it with white
  if(data->rgb.size() == 0){
    for(int i=0; i<file->xyz.size(); i++){
      data->rgb.push_back(vec4(1,1,1,1));
    }
  }

  //---------------------------
  return data;
}

//Import function
utl::media::File* Importer::import_from_path(utl::media::Path path){
  utl::media::File* file = nullptr;
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

      file = importer->import(path);
    }
  }

  //---------------------------
  return file;
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
