#pragma once

#include <Utility/Specific/Common.h>



namespace utl::media{

utl::media::Image load_image(std::string path);
bool is_device_connected(const std::string& devicePath);

}
