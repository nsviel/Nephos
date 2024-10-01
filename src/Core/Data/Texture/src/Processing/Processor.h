#pragma once

#include <Utility/Base/Data/Texture.h>
#include <string>


namespace dat::img{

void load_image_data(utl::base::Image& image, std::string path);
void add_alpha_channel(utl::base::Image& image);

}
