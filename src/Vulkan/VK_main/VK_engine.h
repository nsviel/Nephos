#ifndef VK_ENGINE_H
#define VK_ENGINE_H

#include <VK_struct/typedef.h>
#include <VK_struct/Struct_data.h>
#include <VK_struct/Struct_vulkan.h>
#include <ELE_specific/common.h>

class ELE_window;
class Struct_param;
class Struct_synchro;
class Struct_vulkan;
class VK_surface;
class VK_instance;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_descriptor;
class VK_texture;
class VK_data;
class VK_viewport;
class VK_reload;
class VK_frame;
class VK_canvas;
class VK_command_buffer;
class VK_imgui;
class VK_render;
class VK_info;


class VK_engine
{
public:
  //Constructor / Destructor
  VK_engine(ELE_window* ele_window);
  ~VK_engine();

public:
  //Main functions
  void init();
  void clean();
  void device_wait_idle();
  void reload_shader(string shader, string subshader);

  //Data function
  void insert_object_in_engine(Object* object);
  void insert_glyph_in_engine(Object* object);
  void remove_object_in_engine(Object* object);

  inline ELE_window* get_ele_window(){return ele_window;}
  inline Struct_param* get_struct_param(){return struct_param;}
  inline Struct_vulkan* get_struct_vulkan(){return struct_vulkan;}
  inline Struct_synchro* get_struct_synchro(){return struct_synchro;}
  inline Struct_renderpass* get_renderpass(int i){return struct_vulkan->vec_renderpass[i];}
  inline VK_render* get_vk_render(){return vk_render;}
  inline VK_imgui* get_vk_imgui(){return vk_imgui;}
  inline VK_info* get_vk_info(){return vk_info;}

  inline std::list<Struct_data*> get_list_data_scene(){return struct_vulkan->list_data_scene;}
  inline std::list<Struct_data*> get_list_data_glyph(){return struct_vulkan->list_data_glyph;}

private:
  ELE_window* ele_window;

  Struct_param* struct_param;
  Struct_synchro* struct_synchro;
  Struct_vulkan* struct_vulkan;

  VK_render* vk_render;
  VK_imgui* vk_imgui;
  VK_surface* vk_surface;
  VK_instance* vk_instance;
  VK_command_buffer* vk_command_buffer;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_descriptor* vk_descriptor;
  VK_texture* vk_texture;
  VK_data* vk_data;
  VK_viewport* vk_viewport;
  VK_reload* vk_reload;
  VK_frame* vk_frame;
  VK_canvas* vk_canvas;
  VK_info* vk_info;

  Timer timer;
  std::list<Object*> list_scene;
  std::list<Object*> list_glyph;
};

#endif
