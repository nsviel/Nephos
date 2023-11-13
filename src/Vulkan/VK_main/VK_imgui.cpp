#include "VK_imgui.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_binding/VK_pool.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>
#include <VK_data/VK_buffer.h>
#include <VK_image/VK_texture.h>
#include <VK_image/VK_image.h>


//Constructor / Destructor
VK_imgui::VK_imgui(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pool = new VK_pool(struct_vulkan);
  this->vk_command = new VK_command(struct_vulkan);
  this->vk_submit = new VK_submit(struct_vulkan);
  this->vk_engine = new VK_engine(struct_vulkan);
  this->vk_image = new VK_image(struct_vulkan);
  this->vk_buffer = new VK_buffer(struct_vulkan);
  this->vk_texture = new VK_texture(struct_vulkan);

  //---------------------------
}
VK_imgui::~VK_imgui(){}

//Main function
void VK_imgui::init(){
  Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");
  //---------------------------

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForVulkan(struct_vulkan->window.glfw_window, true);
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = struct_vulkan->instance.instance;
  init_info.PhysicalDevice = struct_vulkan->device.struct_device.physical_device;
  init_info.Device = struct_vulkan->device.device;
  init_info.Queue = struct_vulkan->device.queue_graphics;
  init_info.DescriptorPool = struct_vulkan->pool.descriptor;
  init_info.PipelineCache = VK_NULL_HANDLE;
  init_info.MinImageCount = 3;
  init_info.ImageCount = 3;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  ImGui_ImplVulkan_Init(&init_info, renderpass->renderpass);

  //---------------------------
}
void VK_imgui::draw(VkCommandBuffer& command_buffer){
  //---------------------------

  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(draw_data, command_buffer);

  //---------------------------
}
void VK_imgui::load_font(){
  VkResult result;
  //---------------------------

  Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");
  Struct_subpass* subpass = renderpass->vec_subpass[0];

  vk_pool->reset_command_pool();
  vk_command->start_command_buffer_once(subpass->command_buffer);

  ImGui_ImplVulkan_CreateFontsTexture(subpass->command_buffer);

  vk_command->stop_command_buffer(subpass->command_buffer);
  vk_submit->submit_command_graphics(subpass->command_buffer);
  vk_engine->device_wait_idle();

  ImGui_ImplVulkan_DestroyFontUploadObjects();

  //---------------------------
}
void VK_imgui::clean(){
  //---------------------------

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}


VkDeviceSize VK_imgui::calculateImageSize(VkFormat format, VkExtent3D extent) {
    // Get the number of bytes per pixel for the specified format
    VkFormatProperties formatProperties;
    vkGetPhysicalDeviceFormatProperties(struct_vulkan->device.struct_device.physical_device, format, &formatProperties);

    if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == 0) {
        // Format does not support linear tiling, use optimal tiling instead
        // You may need to handle this differently based on your specific requirements
        // In this example, we'll assume optimal tiling support
        vkGetPhysicalDeviceFormatProperties(struct_vulkan->device.struct_device.physical_device, format, &formatProperties);
    }

    VkDeviceSize bytesPerPixel = 0;

    switch (format) {
        case VK_FORMAT_R8_UNORM:
            bytesPerPixel = 1;
            break;
        case VK_FORMAT_R8G8_UNORM:
            bytesPerPixel = 2;
            break;
        case VK_FORMAT_R8G8B8A8_UNORM:
            bytesPerPixel = 4;
            break;
        // Add more cases for other formats as needed

        default:
            throw std::runtime_error("Unsupported image format");
    }

    // Calculate the size of the image buffer
    VkDeviceSize imageSize = bytesPerPixel * extent.width * extent.height * extent.depth;

    return imageSize;
}
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <image/stb_image_write.h>
Struct_image* VK_imgui::engine_texture(){
  ImTextureID texture = 0;
  //---------------------------
  //PROBLEM ImGui_ImplVulkan_AddTexture demande que le sampler et view soient créer dans le meme context vulkan que imgui
  // SOlution : recréer les ressources

  Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("edl");
  Struct_framebuffer* frame_edl = renderpass->framebuffer;
  Struct_image* image = &frame_edl->color;




  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_buffer->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_buffer->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);


  vk_command->image_layout_transition_single(image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_texture->copy_image_to_buffer(image, staging_buffer);



  VkExtent3D imageExtent = {image->width, image->height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculateImageSize(image->format, imageExtent);

  // 3. Save staging buffer data to file
  void* mappedData;
  vkMapMemory(struct_vulkan->device.device, staging_mem, 0, bufferSize, 0, &mappedData);


int channels = 4;  // Assuming RGBA data, adjust as needed

std::string filename = "output.png";  // Adjust the file name and format as needed

if (stbi_write_png(filename.c_str(), image->width, image->height, channels, mappedData, image->width * channels) == 0) {
    throw std::runtime_error("Failed to write PNG file!");
}



  vkUnmapMemory(struct_vulkan->device.device, staging_mem);


  //Free memory
  vkDestroyBuffer(struct_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(struct_vulkan->device.device, staging_mem, nullptr);


  //---------------------------
  return image;
}

/*ImTextureID VK_imgui::engine_texture(){
  ImTextureID texture = 0;
  //---------------------------
  //PROBLEM ImGui_ImplVulkan_AddTexture demande que le sampler et view soient créer dans le meme context vulkan que imgui
  // SOlution : recréer les ressources

  Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("edl");
  Struct_framebuffer* frame_edl = renderpass->framebuffer;
  Struct_image* image = &frame_edl->color;



vk_image->create_image_view(image);
vk_image->create_image_sampler(image);



  //VkDescriptorSet descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  //texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
  return texture;
}*/
