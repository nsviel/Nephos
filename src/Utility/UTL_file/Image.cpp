#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <image/stb_image.h>


namespace image{
  //---------------------------

  data::Image load_image(std::string path){
    //---------------------------

    data::Image image;
    image.buffer = stbi_load(path.c_str(), &image.width, &image.height, &image.channel_nb, STBI_rgb_alpha);
    if(!image.buffer){
      std::cout<<"[error] failed to load texture image"<<std::endl;
    }

    //---------------------------
    return image;
  }

  //---------------------------
}
