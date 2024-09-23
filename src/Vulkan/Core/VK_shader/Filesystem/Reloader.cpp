#include "Reloader.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::shader{

//Constructor / Destructor
Reloader::Reloader(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_render = new vk::gui::Render(vk_struct);

  //---------------------------
}
Reloader::~Reloader(){}

//Main function
void Reloader::hot_shader_reload(){
  //---------------------------

  this->reload_renderpass(vk_struct->render.renderpass.geometry);
  //this->reload_renderpass(vk_struct->render.renderpass.postprocess);
  //vk_render->update_render_texture();

  //---------------------------
}

//Subfunction
void Reloader::reload_renderpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    for(auto& [name, pipeline] : subpass->map_pipeline){
      vk_pipeline->recreate_pipeline(renderpass, *pipeline);
    }
  }

  //---------------------------
}

}
