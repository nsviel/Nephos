#pragma once

#include <Utility/Base/Media/Image.h>
#include <string>


namespace utl::media{

utl::media::Image load_image(std::string path);
bool is_device_connected(const std::string& devicePath);

}
