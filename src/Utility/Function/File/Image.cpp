#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <image/stb_image.h>


namespace image{
  //---------------------------

  eng::base::Image load_image(std::string path){
    //---------------------------

    eng::base::Image image;
    uint8_t* data = stbi_load(path.c_str(), &image.width, &image.height, &image.channel_nb, STBI_rgb_alpha);
    size_t size = static_cast<size_t>(image.width) * static_cast<size_t>(image.height) * static_cast<size_t>(image.channel_nb);
    image.data = std::vector<uint8_t>(data, data + size);
    if(image.data.empty()){
      std::cout<<"[error] failed to load texture image"<<std::endl;
    }

    //---------------------------
    return image;
  }

  //---------------------------
}
