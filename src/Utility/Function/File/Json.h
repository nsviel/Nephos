#pragma once

#include <nlohmann/json.hpp>
#include <string>


namespace utl::json{

//Main function
template<typename T> void write_value(const std::string& path, const std::string& key, const T& value);
template<typename T> T read_value(const std::string& path, std::string key);

//Subfunction
nlohmann::json read_json(const std::string& path);
template<typename T> T template_null(const T& value);
bool is_json_file(const std::string& path);

}
