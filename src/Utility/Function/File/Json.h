#pragma once

#include <string>
#include <nlohmann/json.hpp>


namespace utl::json{

nlohmann::json read_json(const std::string& path);
template<typename T> void write_value(const std::string& path, const std::string& key, const T& value);
template<typename T> T read_value(const std::string& path, std::string key);
bool is_json_file(const std::string& path);

}
