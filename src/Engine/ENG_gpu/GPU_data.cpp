#include "GPU_data.h"

#include <VK_engine.h>
#include <VK_data/VK_data.h>


//Constructor / Destructor
GPU_data::GPU_data(VK_engine* vk_engine){
  //---------------------------

  this->vk_data = vk_engine->get_vk_data();;

  //---------------------------
}
GPU_data::~GPU_data(){}

//Main function
void GPU_data::insert_object_in_engine(Object* object){
  //---------------------------

  //Check if object already in engine
  bool is_in_list = false;
  for(int i=0; i<list_scene.size(); i++){
    Object* object_list = *next(list_scene.begin(),i);
    if(object->ID == object_list->ID){
      is_in_list = true;
    }
  }

  //If not, insert it
  if(is_in_list == false){
    list_scene.push_back(object);
    vk_data->insert_scene_object(object);
  }

  //---------------------------
}
void GPU_data::insert_glyph_in_engine(Object* object){
  //---------------------------

  //Check if object already in engine
  bool is_in_list = false;
  for(int i=0; i<list_glyph.size(); i++){
    Object* object_list = *next(list_glyph.begin(),i);
    if(object->ID == object_list->ID){
      is_in_list = true;
    }
  }

  //If not, insert it
  if(is_in_list == false){
    list_glyph.push_back(object);
    vk_data->insert_glyph_object(object);
  }

  //---------------------------
}
void GPU_data::remove_object_in_engine(Object* object){
  //---------------------------

  bool is_in_list = false;
  for(int i=0; i<list_scene.size(); i++){
    Object* object_list = *next(list_scene.begin(),i);
    if(object->ID == object_list->ID){
      list_scene.remove(object_list);
      vk_data->clean_data_scene(object->ID);
    }
  }

  //---------------------------
}
