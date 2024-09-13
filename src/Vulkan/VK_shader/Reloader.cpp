#include "Reloader.h"

#include <Vulkan/Namespace.h>


namespace vk::shader{

//Constructor / Destructor
Reloader::Reloader(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);

  //---------------------------
}
Reloader::~Reloader(){}

//Main function
void Reloader::hot_shader_reload(std::string shader_1, std::string shader_2){
  //---------------------------
/*
  if(shader_1 == "Scene"){
    //vk::structure::Renderpass* renderpass = vk_struct->renderpass.get_renderpass_byName("scene");
    if(renderpass == nullptr) return;
    vk::structure::Subpass* subpass = renderpass->vec_subpass[0];
    vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("point");
    this->recreate_pipeline(renderpass, pipelinor(auto& subpass : renderpass.vec_subpe);
  }
  if(shader_1 == "EDL"){
    //vk::structure::Renderpass* renderpass = vk_struct->renderpass.get_renderpass_byName("edl");
    if(renderpass == nullptr) return;
    vk::structure::Subpass* subpass = renderpass->vec_subpass[0];
    vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("triangle_EDL");
    this->recreate_pipeline(renderpass, pipeline);
  }
*/
  //---------------------------
}
void Reloader::recreate_pipeline(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline){
  //---------------------------

  vk_synchro->wait_idle_and_pause();
  vk_pipeline->clean_pipeline_struct(pipeline);
  vk_pipeline->create_pipeline_struct(*renderpass, pipeline);
  vk_synchro->end_idle();

  //---------------------------
}

}
