#pragma once

#include <Utility/Base/Media/Image.h>
#include <string>


namespace dat::img{

void load_image_data(utl::media::Image& image, std::string path);
void add_alpha_channel(utl::media::Image& image);

}
