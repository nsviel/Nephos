#pragma once

#include <Utility/Base/Media/Image.h>
#include <string>


namespace dat::img{

void load_image_data(utl::media::Image& image, std::string path);
bool is_device_connected(const std::string& devicePath);

}
