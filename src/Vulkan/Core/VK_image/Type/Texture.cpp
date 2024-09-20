#include "Texture.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Texture::Texture(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_buffer = new vk::data::Buffer(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_screenshot = new vk::image::Screenshot(vk_struct);

  //---------------------------
}
Texture::~Texture(){}

//Main function
void Texture::clean(){
  //---------------------------

  auto it =  vk_struct->core.data.list_vk_texture.begin();
  while(it !=  vk_struct->core.data.list_vk_texture.end()){
    std::shared_ptr<vk::structure::Texture> texture = *it;

    //Remove texture elements
    vk_image->clean_image(texture->wrapper);
    vk_buffer->clean_buffer(&texture->stagger);

    //Remove texture from list
    vk_struct->core.data.list_vk_texture.remove(texture);
    it = vk_struct->core.data.list_vk_texture.begin();
  }

  //---------------------------
}

//Texture function
void Texture::insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> utl_image){
  //---------------------------

  //Check image integrity
  if(!utl_image) return;
  if(utl_image->format == "") return;
  if(utl_image->size == 0) return;
  if(utl_image->width == 0) return;
  if(utl_image->height == 0) return;

  //Retrieve data vk object
  auto it_object = vk_struct->core.data.map_vk_object.find(data.UID);
  if(it_object == vk_struct->core.data.map_vk_object.end()) return;
  auto vk_object = it_object->second;

  //Check if image already inserted
  auto it_tex = vk_object->map_texture.find(utl_image->name);
  if(it_tex != vk_object->map_texture.end()) return;

  //Create texture from image
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->image = utl_image;
  this->create_texture(texture);

  //---------------------------
}
void Texture::insert_texture(std::shared_ptr<utl::media::Image> utl_image){
  if(!utl_image || utl_image->size == 0) return;
  //---------------------------

  //Input image checks
  if(utl_image->format == "") return;
  if(utl_image->width == 0 || utl_image->height == 0) return;

  //If the texture exists, update it
  auto texture = query_texture(utl_image->texture_ID);
  if(texture){
    this->update_texture(texture);
  }
  //Else create it
  else{
    texture = std::make_shared<vk::structure::Texture>();
    texture->image = utl_image;
    this->create_texture(texture);
  }

  //---------------------------
}
void Texture::export_texture(std::shared_ptr<utl::media::Image> utl_image){
  //---------------------------

  std::shared_ptr<vk::structure::Texture> texture = query_texture(utl_image->texture_ID);
  if(!texture) return;

  vk_screenshot->export_image_to_jpeg(texture->wrapper);

  //---------------------------
}
void Texture::clean_texture(std::shared_ptr<vk::structure::Texture> texture){
  //---------------------------

  vk_image->clean_image(texture->wrapper);
  vk_buffer->clean_buffer(&texture->stagger);
  texture->image->texture_ID = -1;

  //---------------------------
}

//Texture subfunction
void Texture::update_texture(std::shared_ptr<vk::structure::Texture> texture){
  //---------------------------

  //Check if size hasn't changed
  if(texture->stagger.size < texture->image->size){
    this->clean_texture(texture);
    return;
  }

  vk_mem_transfer->copy_texture_to_gpu(*texture);

  //---------------------------
}
void Texture::create_texture(std::shared_ptr<vk::structure::Texture> texture){
  utl::media::Image& utl_image = *texture->image;
  //---------------------------

  //Create texture container
  VkFormat format = find_texture_format(texture->image);
  if(format == VK_FORMAT_UNDEFINED) return;

  //Create associated vk_image
  texture->wrapper.width = utl_image.width;
  texture->wrapper.height = utl_image.height;
  texture->wrapper.format = format;
  texture->wrapper.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  texture->wrapper.usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
  vk_image->create_image(texture->wrapper);

  //Make associated operation
  vk_mem_allocator->allocate_empty_stagger_buffer(texture->stagger, utl_image.size);
  vk_mem_transfer->copy_texture_to_gpu(*texture);
  vk_struct->core.data.list_vk_texture.push_back(texture);

  //---------------------------
}

//Subfunction
void Texture::clean_texture(vk::structure::Object& vk_object){
  //---------------------------

  for(auto& [name, texture] : vk_object.map_texture){
    this->clean_texture(texture);
  }

  //---------------------------
}
VkFormat Texture::find_texture_format(std::shared_ptr<utl::media::Image> image){
  VkFormat format = VK_FORMAT_UNDEFINED;
  //---------------------------

  if(image->format == "R8G8B8A8_SRGB" || image->format == "MJPEG"){
    format = VK_FORMAT_R8G8B8A8_SRGB;
  }
  else if(image->format == "B8G8R8A8_SRGB"){
    format = VK_FORMAT_B8G8R8A8_SRGB;
  }
  else if(image->format == "R16_UNORM"){
    format = VK_FORMAT_R16_UNORM;
  }
  else if(image->format == "R16_UINT"){
    format = VK_FORMAT_R16_UINT;
  }
  else if(image->format == "R32_UINT"){
    format = VK_FORMAT_R32_UINT;
  }
  else if(image->format == "R16UI"){
    format = VK_FORMAT_R16_UINT;
  }
  else{
    std::cout<<"[error] texture format not recognized [-> "<<image->format<<"]"<<std::endl;
  }

  //---------------------------
  return format;
}
std::shared_ptr<vk::structure::Texture> Texture::query_texture(int UID){
  //---------------------------
/*
  for(auto& texture : vk_struct->core.data.list_vk_texture){
    if(texture->UID == UID){
      return texture;
    }
  }
*/
  //---------------------------
  return nullptr;
}

}
